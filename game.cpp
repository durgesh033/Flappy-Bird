
#include "Game.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

Game::Game()
    : window(VideoMode(800, 600), "Flappy Bird"){
    currentState = GameState::MENU;
    score = 0;
    difficulty = 2;
    selectedOption = 0;

    backgroundTexture.loadFromFile("Graphics/background.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
    800.0f / static_cast<float>(backgroundTexture.getSize().x),
    600.0f / static_cast<float>(backgroundTexture.getSize().y)
    );

    menuBackgroundTexture.loadFromFile("Graphics/menu-background.jpg");
    menuBackgroundSprite.setTexture(menuBackgroundTexture);
    menuBackgroundSprite.setScale(
    800.0f / static_cast<float>(menuBackgroundTexture.getSize().x),
    600.0f / static_cast<float>(menuBackgroundTexture.getSize().y)
    );

    pointBuffer.loadFromFile("Sounds/point.ogg");
    pointSound.setBuffer(pointBuffer);

    hitBuffer.loadFromFile("Sounds/die.ogg");
    hitSound.setBuffer(hitBuffer);

    font.loadFromFile("Fonts/Font.ttf");

    titleText.setFont(font);
    titleText.setString("FLAPPY BIRD");
    titleText.setCharacterSize(48);

    menuText.setFont(font);
    menuText.setString("> EASY\n MEDIUM\n HARD\n\n PRESS ENTER TO START");
    menuText.setCharacterSize(28);

    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::White);
    scoreText.setOutlineThickness(3.f);
    scoreText.setOutlineColor(Color::Black);
    scoreText.setStyle(Text::Bold);

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER\nPress R to Restart");
    gameOverText.setCharacterSize(36);

    titleText.setPosition(220.0f, 100.0f);
    menuText.setPosition(180.0f, 220.0f);
    scoreText.setPosition(20.0f, 20.0f);
    gameOverText.setPosition(180.0f, 250.0f);

    bird.loadBird();

    initializePipes();
}

// Game Loop
// Input -> Update -> Render -> Repeat

void Game::run(){
    while(window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        processEvent();
        update(deltaTime);
        render();
    }
}

void Game::processEvent(){
    Event event;
    while(window.pollEvent(event))
    {
        if(event.type == Event::Closed)
        {
            window.close();
        }
        // MENU STATE

        if(currentState == GameState::MENU) {
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Up){
                    selectedOption--;

                    if(selectedOption < 0){
                        selectedOption = 2;
                    }
                }

                if(event.key.code == Keyboard::Down) {
                    selectedOption++;

                    if(selectedOption > 2) {
                        selectedOption = 0;
                    }
                }

                if(event.key.code == Keyboard::Enter) {
                    difficulty = selectedOption;

                    if(difficulty == 0){
                        for(auto& pipe : pipes){
                            pipe.setGapSize(220.0f);
                            pipe.setMoveSpeed(200.0f);
                        }
                    }

                    else if(difficulty == 1) {
                        for(auto& pipe : pipes) {
                            pipe.setGapSize(180.0f);
                            pipe.setMoveSpeed(250.0f);
                        }
                    }

                    else if(difficulty == 2) {
                        for(auto& pipe : pipes) {
                            pipe.setGapSize(140.0f);
                            pipe.setMoveSpeed(320.0f);
                        }
                    }

                    currentState = GameState::READY;
                }
            }
        }

        // READY STATE

        else if(currentState == GameState::READY){
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Space){
                    currentState = GameState::PLAYING;

                    bird.jump();
                }
            }
        }

        // PLAYING STATE

        else if(currentState == GameState::PLAYING){
            if(event.type == Event::KeyPressed) {
                if(event.key.code == Keyboard::Space) {
                    bird.jump();
                }
            }
        }

        // GAME OVER STATE

        else if(currentState == GameState::GAME_OVER){
            if(event.type == Event::KeyPressed) {
                if(event.key.code == Keyboard::R){
                    restartGame();
                }
            }
        }
    }
}

void Game::update(float deltaTime){
    if(currentState == GameState::PLAYING){
        bird.updateBird(deltaTime);

        for(auto& pipe : pipes){
            pipe.updatePipe(deltaTime);

            if(pipe.isOffScreen()) {
                pipe.resetPipe(1000.0f);
            }
        }

        checkCollisions();
        updateScore();
    }
}

void Game::render(){
    window.clear();

    if(currentState == GameState::MENU){
        window.draw(menuBackgroundSprite);
    }

    else {
        window.draw(backgroundSprite);
    }

    // MENU

    if(currentState == GameState::MENU) {
        string menuString;

        if(selectedOption == 0) {
            menuString =
                "> EASY\n"
                "  MEDIUM\n"
                "  HARD\n\n"
                "Press ENTER to Start";
        }

        else if(selectedOption == 1){
            menuString =
                "  EASY\n"
                "> MEDIUM\n"
                "  HARD\n\n"
                "Press ENTER to Start";
        }

        else if(selectedOption == 2) {
            menuString =
                "  EASY\n"
                "  MEDIUM\n"
                "> HARD\n\n"
                "Press ENTER to Start";
        }

        menuText.setString(menuString);

        window.draw(titleText);
        window.draw(menuText);
    }

    else
    {
        for(auto& pipe : pipes)
        {
            pipe.drawPipe(window);
        }

        bird.drawBird(window);

        window.draw(scoreText);

        if(currentState == GameState::GAME_OVER)
        {
            window.draw(gameOverText);
        }
    }

    window.display();
}

void Game::initializePipes(){
    pipes.clear();

    for(int i = 0; i < 3; i++){
        Pipe pipe;
        pipe.loadPipe();
        pipe.resetPipe(900.0f + i * 300.0f);
        pipes.push_back(pipe);
    }
}

void Game::checkCollisions(){
    for(auto& pipe : pipes){
        if(bird.getSprite().getGlobalBounds().intersects(
            pipe.getTopPipe().getGlobalBounds())){
            currentState = GameState::GAME_OVER;

            hitSound.play();
        }

        if(bird.getSprite().getGlobalBounds().intersects(
            pipe.getBottomPipe().getGlobalBounds())) {
            currentState = GameState::GAME_OVER;

            hitSound.play();
        }
    }

    if(bird.getSprite().getPosition().y < 0){
        currentState = GameState::GAME_OVER;

        hitSound.play();
    }

    if(bird.getSprite().getPosition().y > 550){
        currentState = GameState::GAME_OVER;

        hitSound.play();
    }
}

void Game::updateScore(){
    for(auto& pipe : pipes){
        float pipeRightEdge =
            pipe.getTopPipe().getPosition().x +
            pipe.getTopPipe().getGlobalBounds().width;

        if(!pipe.isScored() &&
           bird.getSprite().getPosition().x > pipeRightEdge){
            pointSound.play();
            score++;
            pipe.setScored(true);
            scoreText.setString("Score: " + to_string(score));
        }
    }
}

void Game::restartGame(){
    score = 0;
    scoreText.setString("Score: 0");
    bird.resetBird();
    initializePipes();

    if(difficulty == 0){
        for(auto& pipe : pipes){
            pipe.setGapSize(220.0f);
            pipe.setMoveSpeed(200.0f);
        }
    }

    else if(difficulty == 1){
        for(auto& pipe : pipes){
            pipe.setGapSize(180.0f);
            pipe.setMoveSpeed(250.0f);
        }
    }

    else if(difficulty == 2){
        for(auto& pipe : pipes){
            pipe.setGapSize(140.0f);
            pipe.setMoveSpeed(320.0f);
        }
    }

    currentState = GameState::READY;
}

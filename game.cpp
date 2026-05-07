#include "Game.h"
#include <optional>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

Game::Game() 
    : window(VideoMode({800, 600}), "Flappy Bird") // Create game window size of 800 x 600 with name Flappy Bird
{
    currentState = GameState::MENU; // game starts at menu screen
    score = 0;
    difficulty = 2; // default difficult is medium
    selectedOption = 0;
    font.openFromFile("Fonts/Font.ttf");
    titleText = Text(font, "FLAPPY BIRD", 48);

    menuText = Text(font, "> EASY\n MEDIUM \n HARD\n\n PRESS ENTER TO START", 28);

    scoreText = Text(font, "Score: 0", 30);

    gameOverText = Text(
        font,
        "GAME OVER\n Press R to Restart",
        36
    );

    titleText.setPosition(Vector2f(220, 100));
    menuText.setPosition(Vector2f(180, 220));
    scoreText.setPosition(Vector2f(20, 20));
    gameOverText.setPosition(Vector2f(180, 250));

    bird.loadBird();
    initializePipes();
    
}


// Game Loop
// Input -> Render -> Update -> Repeat
void Game::run(){
    while (window.isOpen()) { 
        float deltaTime = clock.restart().asSeconds(); // return the elasped time and convert time into float seconds
        processEvent();
        update(deltaTime);
        render();

    }
}

void Game::processEvent(){
    while(const optional event = window.pollEvent()) { // this continously checks the window event
        if (event ->is<Event::Closed.()){
            window.close();
        }

        /*
        1. Check if event is keyboard press
        2. Get keyboard event data
        3. Check which key was pressed
        4. Execute logic
        */

        if (currentState == GameState::MENU) {
          if ( event -> is<Event :: KeyPressed>()){ // Triggers Once per actual key press
            const auto* keyEvent = event->getIf<Event::KeyPressed>(); 
            // basically it is does this event currently contain a Keypressed event
            // if yes return pointer to it if no then return nullptr
            // auto == compilier automatically figures out what type 
            // const == no modify event data means always constant

            if (keyEvent ->code == Keyboard::Key::Up){
                // means was the up key pressed 
                selectedOption --;

                if (selectedOption < 0){
                    selectedOption = 2;
                }
            }
            if (keyEvent -> code == Keyboard::Key::Down){
                selectedOption ++;

                if (selectedOption > 2) {
                    selectedOption = 0;
                }
            }

            if (keyEvent -> code == Keyboard::Key::Enter) {
                difficulty = selectedOption;

                if(difficulty == 0) {
                    for(auto& pipe : pipes) {
                        pipe.setGapSize(220.0f);
                        pipe.setMoveSpeed(200.0f);
                    }
                }

                else if(difficulty == 1) {
                    for(auto& pipe : pipes){
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

                // auto& pipe : pipes means go through the all pipe present inside the vector pipes similar to python loop context

                currentState = GameState::READY;
            }
          }
    }

    // Change the game from menu to playing state and start the game

    else if(currentState == GameState::READY) {
        if ( event -> is <Event::KeyPressed>()){
            const auto* keyEvent = event -> getIf<Event::KeyPressed>();

            if (keyEvent -> code == Keyboard::Key::Space) {
                currentState = GameState::PLAYING;

                bird.jump();
            }
        }
    }
    // Space use for jump

    else if(currentState == GameState::PLAYING){
        if (event -> is <Event::KeyPressed>()){
            const auto* keyEvent = event -> getIf<Event::KeyPressed>();

            if (keyEvent -> code == Keyboard::Key::Space) {
                bird.jump();
            }
        }
    }

    // R use for restart
    
    else if(currentState == GameState::GAME_OVER) {
        if (event -> is <Event::KeyPressed>()) {
            const auto* keyEvent = event ->getIf<Event::KeyPressed>();

            if (keyEvent -> code == Keyboard::Key::R){
                restartGame();
            }
        }
    }
}
}

void Game::update(float deltaTime) {

}

void Game::render(){

}

void Game::initializePipes() {
    pipes.clear(); // Remove all existing pipes from the vector

    for(int i = 0; i < 3; i++) { // Creates 3 pipe pairs
        Pipe pipe;

        pipe.loadPipe();
        pipe.resetPipe(900.0f + i * 300.0f); // spaced the pairs pipe
        pipes.push_back(pipe); // add new element at the end of the vector 
        // [pipe1] [pipe2] [pipe3]
        // also if we call the size fun :: returns how many pipes exist
    }
}

void Game::checkCollisions() {

}

void Game::updateScore() {

}

void Game::restartGame() {

}
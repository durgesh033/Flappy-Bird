#ifndef GAME_H
#define GAME_H
#include <vector>

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

#include "pipe.h"
#include "bird.h"

enum class GameState {
    MENU,
    READY,
    PLAYING,
    GAME_OVER
};

class Game{

    private:
    RenderWindow window; // create the window
    Bird bird;
    vector<Pipe> pipes;

    GameState currentState; // gamestate what is running right now (enumn class)
    Font font; // use the font
    Text scoreText;
    Text titleText;
    Text menuText;
    Text gameOverText;

    Clock clock;
    int score;
    int difficulty;
    int selectedOption;


    public:
    Game(); // window, fonts, text, gamestate, pipes, socre, difficulty
    void run(); //  main game loop (process input > update game > render frame)
    void processEvent(); // keyboard input, window close button, menu selection, jump input, restart input
    void update(float deltaTime); // Handles game updates like bird physics, pipe movement. animation, score updatation, collison checks
    void render(); // Draw everything on screen
    void initializePipes(); // Create multiple pipes objects
    void checkCollisions(); 
    void updateScore();
    void restartGame(); // resets everything


};

#endif
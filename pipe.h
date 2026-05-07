#ifndef PIPE_H
#define PIPE_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Pipe{
    private:
    Texture pipeTexture;
    Sprite topPipe; // visible object for top pipe
    Sprite bottomPipe; // visible object for bottom pipe

    Vector2f positon;
    float gapY; // store vertical centers of opening (randomized)
    float gap_size; // decides the gap size between both pipes
    float mSpeed; // controls the left movement speed
    bool score; // tracks the score when bird cross the pipe pairs

    public:
    Pipe();
    void loadPipe();
    void updatePipe(float deltaTime); // handles leftward movement and update sprite position
    void drawPipe(RenderWindow& window);
    void resetPipe(float newX); // why newx: we may respawn at outside the scrren width (flexible design)
    void randomizeGap(); // difficulty setting (randomize the gaps)

    Sprite getTopPipe(); 
    Sprite getBottomPipe();

    bool isOffScreen(); // checks whether pipe completely moved past left side
    bool isScored(); 
    
    void setScored(bool value);
    void setGapSize(float size);
    void setMoveSpeed(float speed);
};

#endif
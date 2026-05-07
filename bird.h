#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Bird {
    private:
    Texture birdTexture[3]; // 3 texture for different uses like 0 - down flap; 1 - mid falp; 2 - up flap
    Sprite birdSprite;

    Vector2f position;

    // Physics Variables - These three controls bird movement

    float velocity; // +ve = downward and -ve = upward
    float gravity; // constant downarad movement so such that velocity += gravity
    float jumpStrength; // When player presses space velocity = -jumpStrength

    //Animation Variables - Flap Animation

    int animationFrame; // current flap frame
    float animationTimer; // contols when frame should switch

    public:
    Bird(); // default constructor
    void loadBird(); // load the texture file
    void updateBird(float deltaTime); // runs every frame
    void jump(); // jumpStrength becomes negative when jump is pressed
    void animateBird(float deltaTime); //switch the frame of the texture array
    void drawBird(RenderWindow& window); // draw the bird in screen

    Sprite getSprite(); // Used by game for collision detection
    void resetBird(); // when collision detected reset the bird position
};

#endif

#include "bird.h"
using namespace sf;

Bird::Bird() {
    position.x = 100.0f; // 100 pixels from left
    position.y = 300.0f; // 300 pixels from top
    velocity = 0.0f; // Initially has no movement ; Neutral state
    gravity = 900.0f; // Higher value = faster fall
    jumpStrength = 350.0f; // How strongly bird jumps
    animationFrame = 0; //starts with 0 index means first flap image
    animationTimer = 0.0f; // Animation starts from the zero
}

void Bird::loadBird(){ 
    birdTexture[0].loadFromFile("Graphics/redbird-downflap.png");
    birdTexture[1].loadFromFile("Graphics/redbird-midflap.png");
    birdTexture[2].loadFromFile("Graphics/redbird-upflap.png");

    birdSprite.setTexture(birdTexture[0]);
    birdSprite.setPosition(position);
}

// Runs every frame containing gravity, falling, movement, sprite sync
void Bird::updateBird(float deltaTime){
    velocity += gravity * deltaTime;
    position.y += velocity * deltaTime;
    birdSprite.setPosition(position);
}

void Bird::jump(){
    
}

void animateBird(float deltaTime){

}

void drawBird(RenderWindow& window){

}

Sprite Bird::getSprite(){

}

void Bird::resetBird(){

}
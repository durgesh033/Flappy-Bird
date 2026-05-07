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
void Bird::updateBird(float deltaTime){ // usually dt = 0.016 (60 FPS)
    velocity += gravity * deltaTime;
    position.y += velocity * deltaTime;
    birdSprite.setPosition(position);
    animateBird(deltaTime);
}

void Bird::jump(){ 
    velocity = -jumpStrength;
}

void Bird::animateBird(float deltaTime){
    animationTimer += deltaTime; // 0.016, 0.032, 0.048

    if (animationTimer >= 0.1f){ // 0.1 is balanced if i do 0.05 then animation will be too fast
        animationFrame++; // after some time the timer become 0.1 then the frame change

        if (animationFrame > 2){ // cause there are only 3 images if index out of bounds then it reset
            animationFrame = 0;
        }
        birdSprite.setTexture(birdTexture[animationFrame]); 

        animationTimer = 0.0f; // reset the cycle
    }
}

void Bird::drawBird(RenderWindow& window){
    window.draw(birdSprite);
}

Sprite Bird::getSprite(){
    return birdSprite;
}

void Bird::resetBird(){
    position.x = 100.0f;
    position.y = 300.0f;

    velocity = 0.0f;

    animationFrame = 0;
    animationTimer = 0.0f;

    birdSprite.setTexture(birdTexture[0]);
    birdSprite.setPosition(position);


}
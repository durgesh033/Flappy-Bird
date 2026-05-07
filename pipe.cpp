#include "pipe.h"

Texture Pipe::pipeTexture;

Pipe::Pipe(){
    position.x = 900.0f; // slightly off the screen for smooth experience
    position.y = 0.0f; // top vertical edge

    gapY = 250.0f; // default vertical opening
    gapSize = 140.0f; // balanced difficulty
    moveSpeed = 250.0f;
    score = false; 

    loadPipe();
}

void Pipe::loadPipe(){
    pipeTexture.loadFromFile("Graphics/pipe-red.png");

    topPipe.setTexture(pipeTexture);
    bottomPipe.setTexture(pipeTexture);

    // Scale pipes
    topPipe.setScale(0.5f, -4.f);
    bottomPipe.setScale(0.5f, 4.f);

    // Pipe height after scaling

    float pipeHeight = pipeTexture.getSize().y * 0.5f;

    // TOP PIPE

    topPipe.setPosition(
        position.x,
        gapY - gapSize / 2
    );

    // BOTTOM PIPE

    bottomPipe.setPosition(
        position.x,
        gapY + gapSize / 2
    );
}

void Pipe::updatePipe(float deltaTime){
    position.x -= moveSpeed * deltaTime; // moves left side with real time

    topPipe.setPosition(Vector2f(position.x, gapY - gapSize / 2));
    bottomPipe.setPosition(Vector2f(position.x, gapY + gapSize / 2));
}

void Pipe::drawPipe(RenderWindow& window){
    window.draw(topPipe);
    window.draw(bottomPipe);
}

void Pipe::resetPipe(float newX){
    position.x = newX; // moves pipe to the right side ex - resetPipe(1000) so now x value is 1000
    randomizeGap(); // create the new gapY
    score = false;

    topPipe.setPosition(Vector2f(position.x, gapY - gapSize / 2));
    bottomPipe.setPosition(Vector2f(position.x, gapY + gapSize / 2));
}

void Pipe::randomizeGap() {
    gapY = 150.0f + static_cast<float>(rand() % 300); // range from 150 to 449
    // why static_cast usually rand give the int value so to convert that value to float we used that
}

Sprite& Pipe::getTopPipe() {
    return topPipe;
}

Sprite& Pipe::getBottomPipe() {
    return bottomPipe;
}

bool Pipe::isOffScreen() {
    if (position.x + topPipe.getGlobalBounds().width < 0){
        // postion.x < 0 == x = -10 and width = 80 so -10 + 80 = 70 so still pipe is visible they are not outside of the screen width
        // thats why we use position + pipeWidth
        // topPipe.getGlobalBounds.size.x == pipeWidth

        return true;
    }
    else {
        return false;
    }
}

bool Pipe::isScored() {
    return score;
}

void Pipe::setScored(bool value){
    score = value;
}

void Pipe::setGapSize(float size) {
    gapSize = size;
}

void Pipe::setMoveSpeed(float speed) {
    moveSpeed = speed;
}
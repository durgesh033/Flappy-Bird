#include "pipe.h"

Pipe::Pipe(){
    positon.x = 900.0f; // slightly off the screen for smooth experience
    positon.y = 0.0f; // top vertical edge

    gapY = 250.0f; // default vertical opening
    gap_size = 180.0f; // balanced difficulty
    mSpeed = 250.0f;
    score = false; 
}

void Pipe::loadPipe(){
    pipeTexture.loadFromFile("Graphics/pipe-green.png");
    topPipe.setTexture(pipeTexture);
    bottomPipe.setTexture(pipeTexture);

    topPipe.setRotation(degrees(180)); // rotates the top pipe

    topPipe.setPosition(Vector2f(positon.x, gapY - gap_size / 2));
    // gapy = 250, gapize = 180 == gapsize /2 = 90  250 - 90 = 160(y value)

    bottomPipe.setPosition(Vector2f(positon.x, gapY + gap_size / 2));
    // same concept but with + sign (cause we need it from bottom so it produces high x value)

    // from topPipe = 160 and bottomPipe = 340 and difference between them = 180 which is the gap Size
}

void Pipe::updatePipe(float deltaTime){
    positon.x -= mSpeed * deltaTime; // moves left side with real time

    topPipe.setPosition(Vector2f(positon.x, gapY - gap_size / 2));
    bottomPipe.setPosition(Vector2f(positon.x, gapY + gap_size / 2));
}

void Pipe::drawPipe(RenderWindow& window){
    window.draw(topPipe);
    window.draw(bottomPipe);
}

void Pipe::resetPipe(float newX){
    positon.x = newX; // moves pipe to the right side ex - resetPipe(1000) so now x value is 1000
    randomizeGap(); // create the new gapY
    score = false;

    topPipe.setPosition(Vector2f(positon.x, gapY - gap_size / 2));
    bottomPipe.setPosition(Vector2f(positon.x, gapY + gap_size / 2));
}

void Pipe::randomizeGap() {
    gapY = 150.0f + static_cast<float>(rand() % 300); // range from 150 to 449
    // why static_cast usually rand give the int value so to convert that value to float we used that
}

Sprite Pipe::getTopPipe() {
    return topPipe;
}

Sprite Pipe::getBottomPipe() {
    return bottomPipe;
}

bool Pipe::isOffScreen() {
    if (positon.x + topPipe.getGlobalBounds.size.x < 0){
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
    gap_size = size;
}

void Pipe::setMoveSpeed(float speed) {
    mSpeed = speed;
}
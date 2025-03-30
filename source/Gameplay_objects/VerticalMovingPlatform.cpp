#include "VerticalMovingPlatform.h"

VerticalMovingPlatform::VerticalMovingPlatform(sf::Texture& image, float x, float y, float w, float h, float range, float spd)
    : Entity(image, x, y, w, h), moveRange(range), speed(spd), movingDown(true) {
    startY = y;
    sprite.setTextureRect(sf::IntRect(1, 417, 64, 16));
}

void VerticalMovingPlatform::update(float time) {
    float nextY = rect.top + (movingDown ? speed : -speed) * time;

    if (nextY > startY + moveRange) {
        movingDown = false;
        nextY = startY + moveRange;
    }
    else if (nextY < startY - moveRange) {
        movingDown = true;
        nextY = startY - moveRange;
    }

    rect.top = nextY;
    dy = (movingDown ? speed : -speed);
}
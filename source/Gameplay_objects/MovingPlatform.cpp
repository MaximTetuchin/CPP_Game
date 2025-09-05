/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(sf::Texture &image, float x, float y, float w, float h, float range, float spd)
    : Entity(image, x, y, w, h), moveRange(range), speed(spd), movingRight(true) {
    startX = x;
    sprite.setTextureRect(sf::IntRect(1, 417, 64, 16));
}

void MovingPlatform::update(float time) {
    float nextX = rect.left + (movingRight ? speed : -speed) * time;

    if (nextX > startX + moveRange) {
        movingRight = false;
        nextX = startX + moveRange;
    } else if (nextX < startX - moveRange) {
        movingRight = true;
        nextX = startX - moveRange;
    }

    rect.left = nextX;
    dx = (movingRight ? 2*speed : -2*speed);
}
#include "ArmoredFlyingEnemy.h"

ArmoredFlyingEnemy::ArmoredFlyingEnemy(sf::Texture& image, float x, float y, float w, float h,
                                     float speed, float range)
    : FlyingEnemy(image, x, y, w, h, speed, range) {
    armor = 10;
    sprite.setTextureRect(sf::IntRect(0, 0, 47, 45));
}
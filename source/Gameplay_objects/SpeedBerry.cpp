#include "SpeedBerry.h"

SpeedBerry::SpeedBerry(sf::Texture& image, float x, float y) 
    : Entity(image, x, y, 10, 9) {
    sprite.setTextureRect(sf::IntRect(36, 311, 10, 9));
}

void SpeedBerry::update(float time) {}
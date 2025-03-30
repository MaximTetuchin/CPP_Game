#include "InvincibilitySphere.h"

InvincibilitySphere::InvincibilitySphere(sf::Texture& image, float x, float y) 
    : Entity(image, x, y, 5, 5) {
    sprite.setTextureRect(sf::IntRect(5, 902, 5, 5));
}

void InvincibilitySphere::update(float time) {}
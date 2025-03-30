#include "Entity.h"

Entity::Entity(sf::Texture &image, float x, float y, float w, float h)
    : rect(x, y, w, h), dx(0), dy(0), isAlive(true) {
    sprite.setTexture(image);
}

void Entity::draw(sf::RenderWindow &window) {
    sprite.setPosition(rect.left, rect.top);
    window.draw(sprite);
}

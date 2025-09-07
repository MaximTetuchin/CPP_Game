/*!
 * @file Entity.cpp
 * @brief Entity base class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Entity
 * @brief Implementation of the base Entity class
 * @ingroup Entities
 */

#include "Entity.h"

/*!
 * @brief Constructs an Entity with specified properties
 * @param image Texture for the entity sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * @param w Width of the entity's collision rectangle
 * @param h Height of the entity's collision rectangle
 * 
 * Initializes the entity with a position, size, and texture. Sets default
 * velocity values to zero and marks the entity as alive.
 */
Entity::Entity(sf::Texture &image, float x, float y, float w, float h)
    : rect(x, y, w, h), dx(0), dy(0), isAlive(true) {
    sprite.setTexture(image);
}

/*!
 * @brief Renders the entity to the specified window
 * @param window Reference to the SFML render window
 * 
 * Updates the sprite's position to match the entity's current position
 * and draws it to the window. This method can be overridden by derived
 * classes for custom rendering behavior.
 */
void Entity::draw(sf::RenderWindow &window) {
    sprite.setPosition(rect.left, rect.top);
    window.draw(sprite);
}
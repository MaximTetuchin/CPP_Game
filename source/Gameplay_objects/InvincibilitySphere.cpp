/*!
 * @file InvincibilitySphere.cpp
 * @brief InvincibilitySphere class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class InvincibilitySphere
 * @brief Implementation of the invincibility sphere functionality
 * @ingroup GameplayObjects
 */

#include "InvincibilitySphere.h"

/*!
 * @brief Constructs an InvincibilitySphere with specified properties
 * @param image Texture for the invincibility sphere sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * 
 * Initializes the invincibility sphere with a specific texture rectangle (5x5 pixels)
 * from the tileset. The sphere is a static collectible object that
 * grants temporary invincibility when collected by the player.
 */
InvincibilitySphere::InvincibilitySphere(sf::Texture& image, float x, float y) 
    : Entity(image, x, y, 5, 5) {
    sprite.setTextureRect(sf::IntRect(5, 902, 5, 5));
}

/*!
 * @brief Updates the invincibility sphere's state
 * @param time Time elapsed since last update (unused)
 * 
 * The invincibility sphere is a static collectible and doesn't require any per-frame updates.
 * Collision detection with the player is handled externally in the main game loop.
 * This method is empty but maintained for interface consistency.
 */
void InvincibilitySphere::update(float time) {}
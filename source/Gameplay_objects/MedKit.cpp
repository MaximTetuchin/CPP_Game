/*!
 * @file MedKit.cpp
 * @brief MedKit class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class MedKit
 * @brief Implementation of the medical kit functionality
 * @ingroup GameplayObjects
 */

#include "MedKit.h"

/*!
 * @brief Constructs a MedKit with specified properties
 * @param image Texture for the medkit sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * 
 * Initializes the medkit with a specific texture rectangle (7x6 pixels)
 * from the tileset. The medkit is a static collectible object that
 * restores player health when collected.
 */
MedKit::MedKit(sf::Texture& image, float x, float y) 
    : Entity(image, x, y, 7, 6) {
    sprite.setTextureRect(sf::IntRect(100, 693, 7, 6));
}

/*!
 * @brief Updates the medkit's state
 * @param time Time elapsed since last update (unused)
 * 
 * The medkit is a static collectible and doesn't require any per-frame updates.
 * Collision detection with the player is handled externally in the main game loop.
 * This method is empty but maintained for interface consistency.
 */
void MedKit::update(float time) {}
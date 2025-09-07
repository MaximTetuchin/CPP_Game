/*!
 * @file SpeedBerry.cpp
 * @brief SpeedBerry class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class SpeedBerry
 * @brief Implementation of the speed berry functionality
 * @ingroup GameplayObjects
 */

#include "SpeedBerry.h"

/*!
 * @brief Constructs a SpeedBerry with specified properties
 * @param image Texture for the speed berry sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * 
 * Initializes the speed berry with a specific texture rectangle (10x9 pixels)
 * from the tileset. The speed berry is a static collectible object that
 * provides a temporary speed boost when collected by the player.
 */
SpeedBerry::SpeedBerry(sf::Texture& image, float x, float y) 
    : Entity(image, x, y, 10, 9) {
    sprite.setTextureRect(sf::IntRect(36, 311, 10, 9));
}

/*!
 * @brief Updates the speed berry's state
 * @param time Time elapsed since last update (unused)
 * 
 * The speed berry is a static collectible and doesn't require any per-frame updates.
 * Collision detection with the player is handled externally in the main game loop.
 * This method is empty but maintained for interface consistency.
 */
void SpeedBerry::update(float time) {}
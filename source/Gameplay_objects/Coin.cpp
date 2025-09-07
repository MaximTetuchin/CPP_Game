/*!
 * @file Coin.cpp
 * @brief Coin class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Coin
 * @brief Implementation of the coin collectible functionality
 * @ingroup GameplayObjects
 */

#include "Coin.h"

/*!
 * @brief Constructs a Coin with specified properties
 * @param image Texture for the coin sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * 
 * Initializes the coin with a specific texture rectangle (7x8 pixels)
 * from the tileset. The coin is a static collectible object that
 * increases the player's currency when collected.
 */
Coin::Coin(sf::Texture &image, float x, float y) 
    : Entity(image, x, y, 7, 8) {
    sprite.setTextureRect(sf::IntRect(4, 1348, 7, 8)); 
}

/*!
 * @brief Updates the coin's state
 * @param time Time elapsed since last update (unused)
 * 
 * The coin is a static collectible and doesn't require any per-frame updates.
 * Collision detection with the player is handled externally in the main game loop.
 * This method is empty but maintained for interface consistency.
 */
void Coin::update(float time) {}
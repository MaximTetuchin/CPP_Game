/*!
 * @file WinBlock.cpp
 * @brief WinBlock class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class WinBlock
 * @brief Implementation of the win block functionality
 * @ingroup GameplayObjects
 */

#include "WinBlock.h"

/*!
 * @brief Constructs a WinBlock with specified properties
 * @param image Texture for the win block sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * 
 * Initializes the win block with a specific texture rectangle (32x32 pixels)
 * from the tileset. The win block is a static object that serves as a
 * trigger for the level completion condition.
 */
WinBlock::WinBlock(sf::Texture& image, float x, float y) 
    : Entity(image, x, y, 32, 32) {
    sprite.setTextureRect(sf::IntRect(112, 208, 32, 32));
}

/*!
 * @brief Updates the win block's state
 * @param time Time elapsed since last update (unused)
 * 
 * The win block is a static object and doesn't require any per-frame updates.
 * Collision detection with the player is handled externally in the main game loop.
 * This method is empty but maintained for interface consistency.
 */
void WinBlock::update(float time) {}
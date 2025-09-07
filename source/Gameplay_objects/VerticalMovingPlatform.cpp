/*!
 * @file VerticalMovingPlatform.cpp
 * @brief VerticalMovingPlatform class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class VerticalMovingPlatform
 * @brief Implementation of the vertical moving platform functionality
 * @ingroup GameplayObjects
 */

#include "VerticalMovingPlatform.h"

/*!
 * @brief Constructs a VerticalMovingPlatform with specified properties
 * @param image Texture for the platform sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * @param w Width of the platform
 * @param h Height of the platform
 * @param range Maximum vertical movement range from start position
 * @param spd Movement speed in pixels per millisecond
 * 
 * Initializes the platform with a specific texture rectangle (64x16 pixels)
 * and sets up its movement parameters. Starts moving downward by default.
 */
VerticalMovingPlatform::VerticalMovingPlatform(sf::Texture& image, float x, float y, float w, float h, float range, float spd)
    : Entity(image, x, y, w, h), moveRange(range), speed(spd), movingDown(true) {
    startY = y;
    sprite.setTextureRect(sf::IntRect(1, 417, 64, 16));
}

/*!
 * @brief Updates the platform's vertical movement
 * @param time Time elapsed since last update in milliseconds
 * 
 * Moves the platform vertically within its defined range. Reverses direction
 * when reaching the upper or lower movement boundaries. Updates the velocity
 * component (dy) for collision detection purposes.
 */
void VerticalMovingPlatform::update(float time) {
    // Calculate next Y position based on current direction
    float nextY = rect.top + (movingDown ? speed : -speed) * time;

    // Check if reached bottom boundary
    if (nextY > startY + moveRange) {
        movingDown = false;
        nextY = startY + moveRange;
    }
    // Check if reached top boundary
    else if (nextY < startY - moveRange) {
        movingDown = true;
        nextY = startY - moveRange;
    }

    // Update position and velocity
    rect.top = nextY;
    dy = (movingDown ? speed : -speed);
}
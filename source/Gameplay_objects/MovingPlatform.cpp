/*!
 * @file MovingPlatform.cpp
 * @brief MovingPlatform class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class MovingPlatform
 * @brief Implementation of the horizontal moving platform functionality
 * @ingroup GameplayObjects
 */

#include "MovingPlatform.h"

/*!
 * @brief Constructs a MovingPlatform with specified properties
 * @param image Texture for the platform sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * @param w Width of the platform
 * @param h Height of the platform
 * @param range Maximum horizontal movement range from start position
 * @param spd Movement speed in pixels per millisecond
 * 
 * Initializes the platform with a specific texture rectangle (64x16 pixels)
 * and sets up its movement parameters. Starts moving right by default.
 */
MovingPlatform::MovingPlatform(sf::Texture &image, float x, float y, float w, float h, float range, float spd)
    : Entity(image, x, y, w, h), moveRange(range), speed(spd), movingRight(true) {
    startX = x;
    sprite.setTextureRect(sf::IntRect(1, 417, 64, 16));
}

/*!
 * @brief Updates the platform's horizontal movement
 * @param time Time elapsed since last update in milliseconds
 * 
 * Moves the platform horizontally within its defined range. Reverses direction
 * when reaching the left or right movement boundaries. Updates the velocity
 * component (dx) for collision detection and player movement purposes.
 * 
 * @note The dx velocity is set to twice the movement speed to ensure proper
 *       player movement when standing on the platform.
 */
void MovingPlatform::update(float time) {
    // Calculate next X position based on current direction
    float nextX = rect.left + (movingRight ? speed : -speed) * time;

    // Check if reached right boundary
    if (nextX > startX + moveRange) {
        movingRight = false;
        nextX = startX + moveRange;
    }
    // Check if reached left boundary
    else if (nextX < startX - moveRange) {
        movingRight = true;
        nextX = startX - moveRange;
    }

    // Update position and velocity
    rect.left = nextX;
    dx = (movingRight ? 2*speed : -2*speed);
}
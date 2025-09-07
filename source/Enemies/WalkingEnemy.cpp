/*!
 * @file WalkingEnemy.cpp
 * @brief WalkingEnemy class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class WalkingEnemy
 * @brief Implementation of the walking enemy functionality
 * @ingroup Enemies
 */

#include "WalkingEnemy.h"
#include "../Gameplay_objects/Tilemap.h"

/*!
 * @brief Constructs a WalkingEnemy with specified properties
 * @param image Texture for the enemy sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * @param w Width of the enemy collision box
 * @param h Height of the enemy collision box
 * @param speed Movement speed of the enemy
 * @param range Patrol range from starting position
 * 
 * Initializes the walking enemy with a specific texture rectangle (34x45 pixels)
 * and sets up its movement parameters. Starts with onGround set to false.
 */
WalkingEnemy::WalkingEnemy(sf::Texture &image, float x, float y, float w, float h,
                         float speed, float range)
    : Enemy(image, x, y, w, h, 0, speed, range), 
      onGround(false) {
    sprite.setTextureRect(sf::IntRect(0, 0, 34, 45));
}

/*!
 * @brief Updates the enemy's movement and state
 * @param time Time elapsed since last update in milliseconds
 * 
 * Handles horizontal patrol movement within the defined range.
 * Applies gravity when not on ground and processes vertical movement.
 * Calls collision detection for both horizontal and vertical directions.
 */
void WalkingEnemy::update(float time) {
    // Calculate next X position and check patrol boundaries
    float nextX = rect.left + speed * time;

    if (nextX < startX - moveRange || nextX > startX + moveRange) {
        speed = -speed;
        nextX = rect.left + speed * time;
    }

    // Update horizontal position and check collisions
    rect.left = nextX;
    Collision(0);

    // Apply gravity and update vertical position
    if(!onGround) dy += 0.0005 * time;
    rect.top += dy * time;
    onGround = false;
    Collision(1);
}

/*!
 * @brief Handles collision detection with tiles
 * @param dir Direction of collision (0 = horizontal, 1 = vertical)
 * 
 * Checks for collisions with grass tiles ('B') and adjusts the enemy's
 * position and movement accordingly. Handles wall bouncing and ground detection.
 */
void WalkingEnemy::Collision(int dir) {
    for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
        for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
            if (TileMap[i][j] == 'B') {
                if ((speed > 0) && (dir == 0)) rect.left = j * 32 - rect.width;
                if ((speed < 0) && (dir == 0)) rect.left = j * 32 + 32;
                if ((dy > 0) && (dir == 1)) { 
                    rect.top = i * 32 - rect.height; 
                    dy = 0; 
                    onGround = true; 
                }
                if ((dy < 0) && (dir == 1)) { 
                    rect.top = i * 32 + 32; 
                    dy = 0; 
                }
            }
        }
}
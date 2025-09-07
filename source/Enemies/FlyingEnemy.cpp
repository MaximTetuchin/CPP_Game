/*!
 * @file FlyingEnemy.cpp
 * @brief FlyingEnemy class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class FlyingEnemy
 * @brief Implementation of the flying enemy functionality
 * @ingroup Enemies
 */

#include "FlyingEnemy.h"
#include "../Gameplay_objects/Tilemap.h"

/*!
 * @brief Constructs a FlyingEnemy with specified properties
 * @param image Texture for the enemy sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * @param w Width of the enemy collision box
 * @param h Height of the enemy collision box
 * @param speed Movement speed of the enemy
 * @param range Patrol range from starting position
 * 
 * Initializes the flying enemy with a specific texture rectangle (42x42 pixels)
 * and sets up its horizontal patrol movement parameters.
 */
FlyingEnemy::FlyingEnemy(sf::Texture &image, float x, float y, float w, float h,
                        float speed, float range)
    : Enemy(image, x, y, w, h, 0, speed, range) {
    sprite.setTextureRect(sf::IntRect(0, 0, 42, 42));
}

/*!
 * @brief Updates the enemy's flying movement and state
 * @param time Time elapsed since last update in milliseconds
 * 
 * Handles horizontal flying movement within patrol boundaries.
 * Reverses direction when reaching movement limits. Flying enemies
 * are not affected by gravity and maintain constant altitude.
 */
void FlyingEnemy::update(float time) {
    // Calculate next X position and check patrol boundaries
    float nextX = rect.left + speed * time;

    if (nextX < startX - moveRange || nextX > startX + moveRange) {
        speed = -speed;
        nextX = rect.left + speed * time;
    }

    // Update horizontal position and check collisions
    rect.left = nextX;
    Collision(0);
}

/*!
 * @brief Handles collision detection for flying enemy
 * @param dir Direction of collision (0 = horizontal, 1 = vertical)
 * 
 * Processes horizontal collisions with grass tiles ('B'). Flying enemies
 * only check horizontal collisions as they are not affected by gravity
 * or ground collisions. Bounces off walls when encountering obstacles.
 */
void FlyingEnemy::Collision(int dir) {
    if (dir == 0) {
        for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
            for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
                if (TileMap[i][j] == 'B') {
                    if (speed > 0) rect.left = j * 32 - rect.width;
                    else if (speed < 0) rect.left = j * 32 + 32;
                }
            }
        }
    }
}
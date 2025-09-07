/*!
 * @file JumpingEnemy.cpp
 * @brief JumpingEnemy class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class JumpingEnemy
 * @brief Implementation of the jumping enemy functionality
 * @ingroup Enemies
 */

#include "JumpingEnemy.h"

/*!
 * @brief Constructs a JumpingEnemy with specified properties
 * @param image Texture for the enemy sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * @param w Width of the enemy collision box
 * @param h Height of the enemy collision box
 * @param speed Movement speed of the enemy
 * @param range Patrol range from starting position
 * @param jumpForce Vertical velocity applied when jumping
 * 
 * Initializes the jumping enemy with a specific texture rectangle (39x45 pixels)
 * and sets up randomized jump timing between 2-5 seconds.
 */
JumpingEnemy::JumpingEnemy(sf::Texture &image, float x, float y, float w, float h,
                          float speed, float range, float jumpForce)
    : WalkingEnemy(image, x, y, w, h, speed, range),
      jumpForce(jumpForce) {
    jumpInterval = rand() % 3000 + 2000;
    jumpTimer = jumpInterval;
    sprite.setTextureRect(sf::IntRect(0, 0, 39, 45)); 
}

/*!
 * @brief Updates the enemy's movement, jumping, and state
 * @param time Time elapsed since last update in milliseconds
 * 
 * Handles the jumping timer and triggers jumps when the timer expires
 * and the enemy is on ground. Uses randomized jump intervals between
 * 2-5 seconds for unpredictable behavior. Calls the parent class update
 * for standard walking enemy behavior.
 */
void JumpingEnemy::update(float time) {
    // Update jump timer
    jumpTimer -= time;
    
    // Jump when timer expires and enemy is on ground
    if(jumpTimer <= 0 && onGround) {
        dy = -jumpForce;
        onGround = false;

        // Randomize next jump interval between 2000-5000 ms (2-5 seconds)
        jumpInterval = rand() % 3000 + 2000;
        jumpTimer = jumpInterval;
    }

    // Call parent class update for walking behavior
    WalkingEnemy::update(time);
}
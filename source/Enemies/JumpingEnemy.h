/*!
 * @file JumpingEnemy.h
 * @brief JumpingEnemy class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class JumpingEnemy
 * @brief Enemy that walks and periodically jumps toward the player
 * @ingroup Enemies
 * 
 * Inherits from WalkingEnemy and adds jumping behavior. This enemy
 * patrols like a walking enemy but also periodically jumps, making
 * it more challenging to avoid.
 */

#ifndef JUMPING_ENEMY_H
#define JUMPING_ENEMY_H
#include "WalkingEnemy.h"

class JumpingEnemy : public WalkingEnemy {
private:
    float jumpTimer;        ///< Timer tracking time until next jump
    float jumpInterval;     ///< Time interval between jumps
    float jumpForce;        ///< Vertical velocity applied when jumping
    
public:
    /*!
     * @brief Constructs a JumpingEnemy object
     * @param image Texture for the enemy sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     * @param w Width of the enemy collision box
     * @param h Height of the enemy collision box
     * @param speed Movement speed of the enemy
     * @param range Patrol range from starting position
     * @param jumpForce Vertical velocity applied when jumping (default: 0.35f)
     */
    JumpingEnemy(sf::Texture &image, float x, float y, float w, float h,
                float speed, float range, float jumpForce = 0.35f);
    
    /*!
     * @brief Updates the enemy's movement, jumping, and state
     * @param time Time elapsed since last update
     * 
     * Handles the jumping enemy's behavior including patrol movement,
     * jump timing, and vertical movement. Periodically jumps when on ground.
     */
    void update(float time) override;
}; 

#endif
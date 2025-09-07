/*!
 * @file ArmoredJumpingEnemy.h
 * @brief ArmoredJumpingEnemy class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class ArmoredJumpingEnemy
 * @brief Jumping enemy with enhanced armor for increased durability
 * @ingroup Enemies
 * 
 * Inherits from JumpingEnemy and represents an armored variant that
 * has increased damage resistance. Behaves identically to a regular
 * jumping enemy but takes reduced damage due to armor.
 */

#ifndef ARMORED_JUMPING_ENEMY_H
#define ARMORED_JUMPING_ENEMY_H
#include "JumpingEnemy.h"

class ArmoredJumpingEnemy : public JumpingEnemy {
public:
    /*!
     * @brief Constructs an ArmoredJumpingEnemy object
     * @param image Texture for the enemy sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     * @param w Width of the enemy collision box
     * @param h Height of the enemy collision box
     * @param speed Movement speed of the enemy
     * @param range Patrol range from starting position
     * @param jumpForce Vertical velocity applied when jumping (default: 0.35f)
     * 
     * Creates an armored jumping enemy with enhanced damage resistance.
     * The armor value is set internally to provide damage reduction while
     * maintaining the jumping behavior of the base class.
     */
    ArmoredJumpingEnemy(sf::Texture &image, float x, float y, float w, float h,
                       float speed, float range, float jumpForce = 0.35f);
};
#endif
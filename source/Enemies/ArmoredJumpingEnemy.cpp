/*!
 * @file ArmoredJumpingEnemy.cpp
 * @brief ArmoredJumpingEnemy class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class ArmoredJumpingEnemy
 * @brief Implementation of the armored jumping enemy functionality
 * @ingroup Enemies
 */

#include "ArmoredJumpingEnemy.h"

/*!
 * @brief Constructs an ArmoredJumpingEnemy with specified properties
 * @param image Texture for the enemy sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * @param w Width of the enemy collision box
 * @param h Height of the enemy collision box
 * @param speed Movement speed of the enemy
 * @param range Patrol range from starting position
 * @param jumpForce Vertical velocity applied when jumping
 * 
 * Initializes the armored jumping enemy with enhanced armor value (10)
 * and the same texture coordinates as regular jumping enemies. Inherits
 * all jumping behavior from JumpingEnemy but with increased durability.
 */
ArmoredJumpingEnemy::ArmoredJumpingEnemy(sf::Texture &image, float x, float y, float w, float h,
                                        float speed, float range, float jumpForce)
    : JumpingEnemy(image, x, y, w, h, speed, range, jumpForce) {
    armor = 10;
    sprite.setTextureRect(sf::IntRect(0, 0, 39, 45));
}
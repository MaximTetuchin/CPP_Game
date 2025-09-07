/*!
 * @file ArmoredWalkingEnemy.cpp
 * @brief ArmoredWalkingEnemy class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class ArmoredWalkingEnemy
 * @brief Implementation of the armored walking enemy functionality
 * @ingroup Enemies
 */

#include "ArmoredWalkingEnemy.h"

/*!
 * @brief Constructs an ArmoredWalkingEnemy with specified properties
 * @param image Texture for the enemy sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * @param w Width of the enemy collision box
 * @param h Height of the enemy collision box
 * @param speed Movement speed of the enemy
 * @param range Patrol range from starting position
 * 
 * Initializes the armored walking enemy with enhanced armor value (10)
 * and the same texture coordinates as regular walking enemies. Inherits
 * all walking behavior from WalkingEnemy but with increased durability.
 */
ArmoredWalkingEnemy::ArmoredWalkingEnemy(sf::Texture &image, float x, float y, float w, float h,
                                       float speed, float range)
    : WalkingEnemy(image, x, y, w, h, speed, range) {
    armor = 10;
    sprite.setTextureRect(sf::IntRect(0, 0, 34, 45));
}
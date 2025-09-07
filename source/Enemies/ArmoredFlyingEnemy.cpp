/*!
 * @file ArmoredFlyingEnemy.cpp
 * @brief ArmoredFlyingEnemy class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class ArmoredFlyingEnemy
 * @brief Implementation of the armored flying enemy functionality
 * @ingroup Enemies
 */

#include "ArmoredFlyingEnemy.h"

/*!
 * @brief Constructs an ArmoredFlyingEnemy with specified properties
 * @param image Texture for the enemy sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * @param w Width of the enemy collision box
 * @param h Height of the enemy collision box
 * @param speed Movement speed of the enemy
 * @param range Patrol range from starting position
 * 
 * Initializes the armored flying enemy with enhanced armor value (10)
 * and specific texture coordinates (47x45 pixels). Inherits all flying
 * behavior from FlyingEnemy but with increased durability.
 */
ArmoredFlyingEnemy::ArmoredFlyingEnemy(sf::Texture& image, float x, float y, float w, float h,
                                     float speed, float range)
    : FlyingEnemy(image, x, y, w, h, speed, range) {
    armor = 10;
    sprite.setTextureRect(sf::IntRect(0, 0, 47, 45));
}
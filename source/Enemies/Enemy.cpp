/*!
 * @file Enemy.cpp
 * @brief Enemy base class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Enemy
 * @brief Implementation of the base enemy functionality
 * @ingroup Enemies
 */

#include "Enemy.h"

/*!
 * @brief Constructs an Enemy with specified properties
 * @param image Texture for the enemy sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * @param w Width of the enemy collision box
 * @param h Height of the enemy collision box
 * @param armor Damage reduction value (0 = no armor)
 * @param speed Movement speed in pixels per millisecond
 * @param range Maximum patrol range from starting position
 * 
 * Initializes enemy with default health of 100 and sets the starting position
 * reference for patrol behavior. Marks the enemy as alive by default.
 */
Enemy::Enemy(sf::Texture &image, float x, float y, float w, float h,
             int armor, float speed, float range)
    : Entity(image, x, y, w, h),
      armor(armor),
      health(100),
      speed(speed),
      moveRange(range),
      startX(x),
      isAlive(true) {}

/*!
 * @brief Applies damage to the enemy, considering armor reduction
 * @param damage Raw damage amount to apply
 * 
 * Calculates actual damage by subtracting armor from incoming damage.
 * Minimum damage is clamped to zero. Reduces health and checks if
 * the enemy should be marked as dead. Outputs debug information
 * to console about health and armor status.
 */
void Enemy::takeDamage(int damage) {
    int actualDamage = damage - armor;
    if (actualDamage < 0) actualDamage = 0;
    health -= actualDamage;
    std::cout << "Health: " << health << ", Armor: " << armor << std::endl;
    if (health <= 0) isAlive = false;
}
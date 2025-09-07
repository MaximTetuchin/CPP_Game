/*!
 * @file ArmoredFlyingEnemy.h
 * @brief ArmoredFlyingEnemy class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class ArmoredFlyingEnemy
 * @brief Flying enemy with enhanced armor for increased durability
 * @ingroup Enemies
 * 
 * Inherits from FlyingEnemy and represents an armored variant that
 * has increased damage resistance. Behaves identically to a regular
 * flying enemy but takes reduced damage due to armor.
 */

#ifndef ARMORED_FLYING_ENEMY_H
#define ARMORED_FLYING_ENEMY_H
#include "FlyingEnemy.h"

class ArmoredFlyingEnemy : public FlyingEnemy {
public:
    /*!
     * @brief Constructs an ArmoredFlyingEnemy object
     * @param image Texture for the enemy sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     * @param w Width of the enemy collision box
     * @param h Height of the enemy collision box
     * @param speed Movement speed of the enemy
     * @param range Patrol range from starting position
     * 
     * Creates an armored flying enemy with enhanced damage resistance.
     * The armor value is set internally to provide damage reduction while
     * maintaining the flying behavior of the base class.
     */
    ArmoredFlyingEnemy(sf::Texture& image, float x, float y, float w, float h, 
                      float speed, float range);
};
#endif
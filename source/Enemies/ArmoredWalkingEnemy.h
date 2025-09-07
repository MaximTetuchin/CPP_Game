/*!
 * @file ArmoredWalkingEnemy.h
 * @brief ArmoredWalkingEnemy class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class ArmoredWalkingEnemy
 * @brief Walking enemy with enhanced armor for increased durability
 * @ingroup Enemies
 * 
 * Inherits from WalkingEnemy and represents an armored variant that
 * has increased damage resistance. Behaves identically to a regular
 * walking enemy but takes reduced damage due to armor.
 */

#ifndef ARMORED_WALKING_ENEMY_H
#define ARMORED_WALKING_ENEMY_H
#include "WalkingEnemy.h"

class ArmoredWalkingEnemy : public WalkingEnemy {
public:
    /*!
     * @brief Constructs an ArmoredWalkingEnemy object
     * @param image Texture for the enemy sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     * @param w Width of the enemy collision box
     * @param h Height of the enemy collision box
     * @param speed Movement speed of the enemy
     * @param range Patrol range from starting position
     * 
     * Creates an armored walking enemy with enhanced damage resistance.
     * The armor value is set internally to provide damage reduction.
     */
    ArmoredWalkingEnemy(sf::Texture &image, float x, float y, float w, float h,
                      float speed, float range);
};

#endif
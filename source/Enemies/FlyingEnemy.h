/*!
 * @file FlyingEnemy.h
 * @brief FlyingEnemy class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class FlyingEnemy
 * @brief Airborne enemy that flies in patterns and ignores ground collision
 * @ingroup Enemies
 * 
 * Inherits from Enemy and represents a flying enemy that moves through the air
 * without being affected by gravity. Can fly in various patterns and poses
 * a different threat than ground-based enemies.
 */

#ifndef FLYING_ENEMY_H
#define FLYING_ENEMY_H
#include "Enemy.h"

class FlyingEnemy : public Enemy {
public:
    /*!
     * @brief Constructs a FlyingEnemy object
     * @param image Texture for the enemy sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     * @param w Width of the enemy collision box
     * @param h Height of the enemy collision box
     * @param speed Movement speed of the enemy
     * @param range Patrol range from starting position
     */
    FlyingEnemy(sf::Texture &image, float x, float y, float w, float h, 
               float speed, float range);

    /*!
     * @brief Updates the enemy's flying movement and state
     * @param time Time elapsed since last update
     * 
     * Handles aerial movement patterns without gravity. Flies within
     * defined patrol boundaries and reverses direction at limits.
     */
    void update(float time) override;
    
    /*!
     * @brief Handles collision detection for flying enemy
     * @param dir Direction of collision (0 = horizontal, 1 = vertical)
     * 
     * Processes collisions with level boundaries and obstacles.
     * Flying enemies may have different collision behavior than
     * ground-based enemies.
     */
    void Collision(int dir) override;
};
#endif
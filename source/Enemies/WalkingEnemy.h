/*!
 * @file WalkingEnemy.h
 * @brief WalkingEnemy class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class WalkingEnemy
 * @brief Ground-based enemy that walks back and forth on platforms
 * @ingroup Enemies
 * 
 * Inherits from Enemy and represents a basic ground enemy that
 * patrols horizontally on platforms and can damage the player on contact.
 */

#ifndef WALKING_ENEMY_H
#define WALKING_ENEMY_H

#include "Enemy.h"

class WalkingEnemy : public Enemy {
public:
    bool onGround;  ///< Indicates if the enemy is currently on ground
    
    /*!
     * @brief Constructs a WalkingEnemy object
     * @param image Texture for the enemy sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     * @param w Width of the enemy collision box
     * @param h Height of the enemy collision box
     * @param speed Movement speed of the enemy
     * @param range Patrol range from starting position
     */
    WalkingEnemy(sf::Texture &image, float x, float y, float w, float h, 
                float speed, float range);
    
    /*!
     * @brief Updates the enemy's movement and state
     * @param time Time elapsed since last update
     * 
     * Handles horizontal movement, gravity, and patrol behavior.
     * Reverses direction when reaching patrol boundaries or obstacles.
     */
    void update(float time) override;
    
    /*!
     * @brief Handles collision detection and response
     * @param dir Direction of collision (0 = horizontal, 1 = vertical)
     * 
     * Processes collisions with tiles and adjusts movement accordingly.
     * Handles ground detection and wall bouncing.
     */
    void Collision(int dir) override;
};

#endif
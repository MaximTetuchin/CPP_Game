/*!
 * @file Enemy.h
 * @brief Enemy base class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Enemy
 * @brief Base class for all enemy types in the game
 * @ingroup Enemies
 * 
 * Inherits from Entity and provides common functionality for all enemies
 * including health, armor, movement, and damage handling. Serves as the
 * foundation for specialized enemy types.
 */

#ifndef ENEMY_H
#define ENEMY_H
#include "../Entity.h"

class Enemy : public Entity {
public:
    int armor;          ///< Damage reduction value (armor reduces incoming damage)
    int health;         ///< Current health points of the enemy
    float speed;        ///< Movement speed in pixels per millisecond
    float moveRange;    ///< Maximum patrol range from starting position
    float startX;       ///< Initial X coordinate (reference point for movement)
    bool isAlive;       ///< Current alive status of the enemy

    /*!
     * @brief Constructs an Enemy object
     * @param image Texture for the enemy sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     * @param w Width of the enemy collision box
     * @param h Height of the enemy collision box
     * @param armor Damage reduction value (0 = no armor)
     * @param speed Movement speed in pixels per millisecond
     * @param range Maximum patrol range from starting position
     */
    Enemy(sf::Texture &image, float x, float y, float w, float h, 
          int armor, float speed, float range);
    
    /*!
     * @brief Applies damage to the enemy, considering armor
     * @param damage Raw damage amount to apply
     * 
     * Reduces the enemy's health by the damage amount after applying
     * armor reduction. Marks the enemy as dead if health reaches zero.
     */
    virtual void takeDamage(int damage);
    
    /*!
     * @brief Pure virtual update method to be implemented by derived classes
     * @param time Time elapsed since last update
     */
    virtual void update(float time) = 0;
    
    /*!
     * @brief Pure virtual collision method to be implemented by derived classes
     * @param dir Direction of collision (0 = horizontal, 1 = vertical)
     */
    virtual void Collision(int dir) = 0;
};
#endif
/*!
 * @file Bullet.h
 * @brief Bullet class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Bullet
 * @brief Projectile entity fired by weapons
 * @ingroup Weapons
 * 
 * Inherits from Entity and represents a bullet projectile with
 * direction, speed, and damage properties. Handles movement and
 * lifetime management.
 */

#ifndef BULLET_H
#define BULLET_H
#include "../Entity.h"

class Bullet : public Entity {
public:
    bool direction; ///< Movement direction (true = right, false = left)
    float speed;    ///< Movement speed of the bullet
    int damage;     ///< Damage dealt by the bullet on impact

    /*!
     * @brief Constructs a Bullet object
     * @param image Texture for the bullet sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     * @param dir Movement direction (true = right, false = left)
     * @param spd Movement speed of the bullet
     * @param dmg Damage dealt by the bullet
     */
    Bullet(sf::Texture& image, float x, float y, bool dir, float spd, int dmg);
    
    /*!
     * @brief Updates the bullet's position and checks for lifetime
     * @param time Time elapsed since last update
     * 
     * Moves the bullet in its specified direction and speed.
     * Checks if the bullet has gone off-screen and marks it for removal.
     */
    void update(float time) override;
};

#endif
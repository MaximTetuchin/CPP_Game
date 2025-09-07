/*!
 * @file Rifle.h
 * @brief Rifle weapon class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Rifle
 * @brief Rapid-fire rifle weapon with moderate damage
 * @ingroup Weapons
 * 
 * Inherits from Weapon and implements rifle-specific behavior including
 * rapid firing, consistent trajectory, and moderate damage per bullet.
 */

#ifndef RIFLE_H
#define RIFLE_H

#include "Weapon.h"

class Rifle : public Weapon {
private:
    float fireDelay;            ///< Time between shots in milliseconds
    float currentDelay;         ///< Current time since last shot
    sf::Texture bulletTexture;  ///< Texture for rifle bullets
    int damage;                 ///< Damage per bullet

public:
    /*!
     * @brief Constructs a Rifle weapon
     * @param delay Time between shots in milliseconds (default: 200.0f)
     * @param dmg Damage per bullet (default: 18)
     */
    Rifle(float delay = 200.0f, int dmg = 18);
    
    /*!
     * @brief Sets the texture for rifle bullets
     * @param texture Reference to the SFML texture to use for bullets
     */
    void setBulletTexture(sf::Texture& texture) override;
    
    /*!
     * @brief Attempts to fire the rifle
     * @param bullets Reference to the vector where new bullets should be added
     * @param x X coordinate for bullet spawn position
     * @param y Y coordinate for bullet spawn position
     * @param direction Firing direction (true = right, false = left)
     * @return True if the rifle successfully fired, false if on cooldown
     * 
     * Fires a single bullet with consistent trajectory when called.
     * The bullet is added to the bullets vector with standard velocity.
     */
    bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) override;
    
    /*!
     * @brief Updates the rifle's cooldown timer
     * @param time Time elapsed since last update
     */
    void update(float time) override;
    
    /*!
     * @brief Gets the display name of the weapon
     * @return String "Rifle"
     */
    std::string getName() const override;
};

#endif
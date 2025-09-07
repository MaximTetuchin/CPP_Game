/*!
 * @file Minigun.h
 * @brief Minigun weapon class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Minigun
 * @brief Rapid-fire minigun weapon with high rate of fire but lower damage per bullet
 * @ingroup Weapons
 * 
 * Inherits from Weapon and implements minigun-specific behavior including
 * very high firing rate, multiple bullets per shot, and low damage per bullet.
 */

#ifndef MINIGUN_H
#define MINIGUN_H
#include "Weapon.h"

class Minigun : public Weapon {
private:
    float fireDelay;            ///< Time between shots in milliseconds
    float currentDelay;         ///< Current time since last shot
    sf::Texture bulletTexture;  ///< Texture for minigun bullets
    int damage;                 ///< Damage per bullet
    int bulletsPerShot;         ///< Number of bullets fired per trigger pull

public:
    /*!
     * @brief Constructs a Minigun weapon
     * @param delay Time between shots in milliseconds (default: 150.0f)
     * @param dmg Damage per bullet (default: 11)
     * @param bullets Number of bullets fired per shot (default: 3)
     */
    Minigun(float delay = 150.0f, int dmg = 11, int bullets = 3);
    
    /*!
     * @brief Sets the texture for minigun bullets
     * @param texture Reference to the SFML texture to use for bullets
     */
    void setBulletTexture(sf::Texture& texture) override;
    
    /*!
     * @brief Gets the display name of the weapon
     * @return String "Minigun"
     */
    std::string getName() const override;
    
    /*!
     * @brief Attempts to fire the minigun
     * @param bullets Reference to the vector where new bullets should be added
     * @param x X coordinate for bullet spawn position
     * @param y Y coordinate for bullet spawn position
     * @param direction Firing direction (true = right, false = left)
     * @return True if the minigun successfully fired, false if on cooldown
     * 
     * Fires multiple bullets in quick succession when called.
     * Each bullet is added to the bullets vector with similar trajectory.
     */
    bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) override;
    
    /*!
     * @brief Updates the minigun's cooldown timer
     * @param time Time elapsed since last update
     */
    void update(float time) override;
};

#endif
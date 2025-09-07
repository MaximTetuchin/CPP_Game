/*!
 * @file Pistol.h
 * @brief Pistol weapon class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Pistol
 * @brief Standard sidearm weapon with balanced damage and fire rate
 * @ingroup Weapons
 * 
 * Inherits from Weapon and implements pistol-specific behavior including
 * moderate firing rate, balanced damage, and standard bullet trajectory.
 */

#ifndef PISTOL_H
#define PISTOL_H
#include "Weapon.h"

class Pistol : public Weapon {
private:
    float fireDelay;            ///< Time between shots in milliseconds
    float currentDelay;         ///< Current time since last shot
    sf::Texture bulletTexture;  ///< Texture for pistol bullets
    int damage;                 ///< Damage per bullet

public:
    /*!
     * @brief Constructs a Pistol weapon
     * @param delay Time between shots in milliseconds (default: 420.0f)
     * @param dmg Damage per bullet (default: 25)
     */
    Pistol(float delay = 420.0f, int dmg = 25);
    
    /*!
     * @brief Sets the texture for pistol bullets
     * @param texture Reference to the SFML texture to use for bullets
     */
    void setBulletTexture(sf::Texture& texture) override;
    
    /*!
     * @brief Gets the display name of the weapon
     * @return String "Pistol"
     */
    std::string getName() const override;
    
    /*!
     * @brief Attempts to fire the pistol
     * @param bullets Reference to the vector where new bullets should be added
     * @param x X coordinate for bullet spawn position
     * @param y Y coordinate for bullet spawn position
     * @param direction Firing direction (true = right, false = left)
     * @return True if the pistol successfully fired, false if on cooldown
     * 
     * Fires a single bullet with standard trajectory when called.
     * The bullet is added to the bullets vector with balanced velocity.
     */
    bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) override;
    
    /*!
     * @brief Updates the pistol's cooldown timer
     * @param time Time elapsed since last update
     */
    void update(float time) override;
};

#endif
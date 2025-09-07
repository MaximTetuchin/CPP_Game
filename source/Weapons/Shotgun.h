/*!
 * @file Shotgun.h
 * @brief Shotgun weapon class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Shotgun
 * @brief Shotgun weapon that fires multiple pellets in a spread pattern
 * @ingroup Weapons
 * 
 * Inherits from Weapon and implements shotgun-specific behavior including
 * multiple pellet projectiles, spread patterns, and firing delays.
 */

#ifndef SHOTGUN_H
#define SHOTHUN_H  // Note: There's a typo here - should be SHOTGUN_H

#include "Weapon.h"

class Shotgun : public Weapon {
private:
    float fireDelay;            ///< Time between shots in milliseconds
    float currentDelay;         ///< Current time since last shot
    sf::Texture bulletTexture;  ///< Texture for shotgun pellets
    int damage;                 ///< Damage per pellet
    int pelletCount;            ///< Number of pellets per shot

public:
    /*!
     * @brief Constructs a Shotgun weapon
     * @param delay Time between shots in milliseconds (default: 2000.0f)
     * @param dmg Damage per pellet (default: 55)
     * @param pellets Number of pellets per shot (default: 2)
     */
    Shotgun(float delay = 2000.0f, int dmg = 55, int pellets = 2);
    
    /*!
     * @brief Sets the texture for shotgun pellets
     * @param texture Reference to the SFML texture to use for pellets
     */
    void setBulletTexture(sf::Texture& texture) override;
    
    /*!
     * @brief Gets the display name of the weapon
     * @return String "Shotgun"
     */
    std::string getName() const override;
    
    /*!
     * @brief Attempts to fire the shotgun
     * @param bullets Reference to the vector where new pellets should be added
     * @param x X coordinate for pellet spawn position
     * @param y Y coordinate for pellet spawn position
     * @param direction Firing direction (true = right, false = left)
     * @return True if the shotgun successfully fired, false if on cooldown
     * 
     * Fires multiple pellets in a spread pattern when called. Each pellet
     * is added to the bullets vector with slightly different trajectories.
     */
    bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) override;
    
    /*!
     * @brief Updates the shotgun's cooldown timer
     * @param time Time elapsed since last update
     */
    void update(float time) override;
};

#endif
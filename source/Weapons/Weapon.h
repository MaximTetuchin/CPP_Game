/*!
 * @file Weapon.h
 * @brief Weapon base class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Weapon
 * @brief Abstract base class for all weapons in the game
 * @ingroup Weapons
 * 
 * Defines the interface for all weapon types. Derived classes must implement
 * firing mechanics, updates, and weapon-specific properties.
 */

#ifndef WEAPON_H
#define WEAPON_H
#include <vector>
#include <memory>
#include "../Entity.h"

class Weapon {
public:
    /*!
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~Weapon() = default;
    
    /*!
     * @brief Attempts to fire the weapon
     * @param bullets Reference to the vector where new bullets should be added
     * @param x X coordinate for bullet spawn position
     * @param y Y coordinate for bullet spawn position
     * @param direction Firing direction (true = right, false = left)
     * @return True if the weapon successfully fired, false otherwise
     * 
     * Derived classes implement specific firing logic including rate of fire,
     * bullet patterns, and ammunition checks.
     */
    virtual bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) = 0;
    
    /*!
     * @brief Updates the weapon's state
     * @param time Time elapsed since last update
     * 
     * Handles weapon-specific updates such as cooldown timers,
     * animation states, and other time-dependent logic.
     */
    virtual void update(float time) = 0;
    
    /*!
     * @brief Sets the texture for bullets fired by this weapon
     * @param texture Reference to the SFML texture to use for bullets
     */
    virtual void setBulletTexture(sf::Texture& texture) = 0;
    
    /*!
     * @brief Gets the display name of the weapon
     * @return String containing the weapon's name
     */
    virtual std::string getName() const = 0;
};

#endif
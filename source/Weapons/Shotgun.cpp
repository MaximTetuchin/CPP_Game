/*!
 * @file Shotgun.cpp
 * @brief Shotgun weapon class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Shotgun
 * @brief Implementation of the shotgun weapon functionality
 * @ingroup Weapons
 */

#include "Shotgun.h"
#include "Bullet.h"

/*!
 * @brief Constructs a Shotgun with specified parameters
 * @param delay Time between shots in milliseconds
 * @param dmg Damage per pellet
 * @param pellets Number of pellets per shot
 */
Shotgun::Shotgun(float delay, int dmg, int pellets)
    : fireDelay(delay), currentDelay(0), damage(dmg), pelletCount(pellets) {}

/*!
 * @brief Sets the texture for shotgun pellets
 * @param texture Reference to the SFML texture to use for pellets
 */
void Shotgun::setBulletTexture(sf::Texture& texture) {
    bulletTexture = texture;
}

/*!
 * @brief Gets the display name of the weapon
 * @return String "Shotgun"
 */
std::string Shotgun::getName() const {
    return "Shotgun";
}

/*!
 * @brief Attempts to fire the shotgun if not on cooldown
 * @param bullets Reference to the vector where new pellets should be added
 * @param x X coordinate for pellet spawn position
 * @param y Y coordinate for pellet spawn position
 * @param direction Firing direction (true = right, false = left)
 * @return True if the shotgun successfully fired, false if on cooldown
 * 
 * Fires multiple pellets in a spread pattern with slight vertical offset.
 * Each pellet has slightly different trajectory for a realistic shotgun effect.
 * Resets the cooldown timer after firing.
 */
bool Shotgun::tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) {
    if (currentDelay <= 0) {
        for (int i = 0; i < pelletCount; i++) {
            bullets.push_back(new Bullet(bulletTexture,
                x + (direction ? 6 : -6),
                y + 6 + (i * 5),
                direction,
                0.5f + (i * 0.1f),
                damage));
        }
        currentDelay = fireDelay;
        return true;
    }
    return false;
}

/*!
 * @brief Updates the shotgun's cooldown timer
 * @param time Time elapsed since last update in milliseconds
 * 
 * Decrements the current delay by the elapsed time, allowing the weapon
 * to be fired again when the delay reaches zero.
 */
void Shotgun::update(float time) {
    if (currentDelay > 0) currentDelay -= time;
}
/*!
 * @file Rifle.cpp
 * @brief Rifle weapon class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Rifle
 * @brief Implementation of the rifle weapon functionality
 * @ingroup Weapons
 */

#include "Rifle.h"
#include "Bullet.h"

/*!
 * @brief Constructs a Rifle with specified parameters
 * @param delay Time between shots in milliseconds
 * @param dmg Damage per bullet
 */
Rifle::Rifle(float delay, int dmg)
    : fireDelay(delay), currentDelay(0), damage(dmg) {}

/*!
 * @brief Sets the texture for rifle bullets
 * @param texture Reference to the SFML texture to use for bullets
 */
void Rifle::setBulletTexture(sf::Texture& texture) {
    bulletTexture = texture;
}

/*!
 * @brief Attempts to fire the rifle if not on cooldown
 * @param bullets Reference to the vector where new bullets should be added
 * @param x X coordinate for bullet spawn position
 * @param y Y coordinate for bullet spawn position
 * @param direction Firing direction (true = right, false = left)
 * @return True if the rifle successfully fired, false if on cooldown
 * 
 * Fires a single bullet with consistent trajectory and moderate speed.
 * The bullet spawns with a slight offset based on firing direction.
 * Resets the cooldown timer after firing.
 */
bool Rifle::tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) {
    if (currentDelay <= 0) {
        bullets.push_back(new Bullet(bulletTexture,
            x + (direction ? 6 : -6),
            y + 6,
            direction,
            0.7f,
            damage));
        currentDelay = fireDelay;
        return true;
    }
    return false;
}

/*!
 * @brief Updates the rifle's cooldown timer
 * @param time Time elapsed since last update in milliseconds
 * 
 * Decrements the current delay by the elapsed time, allowing the weapon
 * to be fired again when the delay reaches zero.
 */
void Rifle::update(float time) {
    if (currentDelay > 0) currentDelay -= time;
}

/*!
 * @brief Gets the display name of the weapon
 * @return String "Rifle"
 */
std::string Rifle::getName() const {
    return "Rifle";
}
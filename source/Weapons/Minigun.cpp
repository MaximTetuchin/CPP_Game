/*!
 * @file Minigun.cpp
 * @brief Minigun weapon class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Minigun
 * @brief Implementation of the minigun weapon functionality
 * @ingroup Weapons
 */

#include "Minigun.h"
#include "Bullet.h"

/*!
 * @brief Constructs a Minigun with specified parameters
 * @param delay Time between shots in milliseconds
 * @param dmg Damage per bullet
 * @param bullets Number of bullets fired per shot
 */
Minigun::Minigun(float delay, int dmg, int bullets)
    : fireDelay(delay), currentDelay(0), damage(dmg), bulletsPerShot(bullets) {}

/*!
 * @brief Sets the texture for minigun bullets
 * @param texture Reference to the SFML texture to use for bullets
 */
void Minigun::setBulletTexture(sf::Texture& texture) {
    bulletTexture = texture;
}

/*!
 * @brief Gets the display name of the weapon
 * @return String "Minigun"
 */
std::string Minigun::getName() const {
    return "Minigun";
}

/*!
 * @brief Attempts to fire the minigun if not on cooldown
 * @param bullets Reference to the vector where new bullets should be added
 * @param x X coordinate for bullet spawn position
 * @param y Y coordinate for bullet spawn position
 * @param direction Firing direction (true = right, false = left)
 * @return True if the minigun successfully fired, false if on cooldown
 * 
 * Fires multiple bullets in a tight spread pattern with slight vertical offset.
 * Each bullet has slightly different trajectory and speed for a realistic
 * minigun effect. Resets the cooldown timer after firing.
 */
bool Minigun::tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) {
    if (currentDelay <= 0) {
        for (int i = 0; i < bulletsPerShot; i++) {
            bullets.push_back(new Bullet(bulletTexture,
                x + (direction ? 6 : -6),
                y + 6 + (i * 3),
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
 * @brief Updates the minigun's cooldown timer
 * @param time Time elapsed since last update in milliseconds
 * 
 * Decrements the current delay by the elapsed time, allowing the weapon
 * to be fired again when the delay reaches zero.
 */
void Minigun::update(float time) {
    if (currentDelay > 0) currentDelay -= time;
}
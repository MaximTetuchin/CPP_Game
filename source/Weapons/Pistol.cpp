/*!
 * @file Pistol.cpp
 * @brief Pistol weapon class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Pistol
 * @brief Implementation of the pistol weapon functionality
 * @ingroup Weapons
 */

#include "Pistol.h"
#include "Bullet.h"

/*!
 * @brief Constructs a Pistol with specified parameters
 * @param delay Time between shots in milliseconds
 * @param dmg Damage per bullet
 */
Pistol::Pistol(float delay, int dmg)
    : fireDelay(delay), currentDelay(0), damage(dmg) {}

/*!
 * @brief Sets the texture for pistol bullets
 * @param texture Reference to the SFML texture to use for bullets
 */
void Pistol::setBulletTexture(sf::Texture& texture) {
    bulletTexture = texture;
}

/*!
 * @brief Gets the display name of the weapon
 * @return String "Pistol"
 */
std::string Pistol::getName() const {
    return "Pistol";
}

/*!
 * @brief Attempts to fire the pistol if not on cooldown
 * @param bullets Reference to the vector where new bullets should be added
 * @param x X coordinate for bullet spawn position
 * @param y Y coordinate for bullet spawn position
 * @param direction Firing direction (true = right, false = left)
 * @return True if the pistol successfully fired, false if on cooldown
 * 
 * Fires a single bullet with standard trajectory and moderate speed.
 * The bullet spawns with a slight offset based on firing direction.
 * Resets the cooldown timer after firing.
 */
bool Pistol::tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) {
    if (currentDelay <= 0) {
        bullets.push_back(new Bullet(bulletTexture,
            x + (direction ? 6 : -6),
            y + 6,
            direction,
            0.5f,
            damage));
        currentDelay = fireDelay;
        return true;
    }
    return false;
}

/*!
 * @brief Updates the pistol's cooldown timer
 * @param time Time elapsed since last update in milliseconds
 * 
 * Decrements the current delay by the elapsed time, allowing the weapon
 * to be fired again when the delay reaches zero.
 */
void Pistol::update(float time) {
    if (currentDelay > 0) currentDelay -= time;
}
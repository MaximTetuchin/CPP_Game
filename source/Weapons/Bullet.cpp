/*!
 * @file Bullet.cpp
 * @brief Bullet class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Bullet
 * @brief Implementation of the bullet projectile functionality
 * @ingroup Weapons
 */

#include "Bullet.h"
#include "../Gameplay_objects/Tilemap.h"

/*!
 * @brief Constructs a Bullet with specified properties
 * @param image Texture for the bullet sprite
 * @param x Initial X coordinate position
 * @param y Initial Y coordinate position
 * @param dir Movement direction (true = right, false = left)
 * @param spd Movement speed of the bullet
 * @param dmg Damage dealt by the bullet
 * 
 * Initializes the bullet with a specific texture rectangle (8x8 pixels)
 * and sets up its movement properties.
 */
Bullet::Bullet(sf::Texture& image, float x, float y, bool dir, float spd, int dmg)
    : Entity(image, x, y, 8, 8), direction(dir), speed(spd), damage(dmg) {
    sprite.setTextureRect(sf::IntRect(247, 583, 8, 8));
}

/*!
 * @brief Updates the bullet's position and checks for collisions
 * @param time Time elapsed since last update in milliseconds
 * 
 * Moves the bullet in its specified direction and speed.
 * Checks for collisions with grass tiles ('B') and screen boundaries.
 * Marks the bullet as not alive when it hits obstacles or goes off-screen.
 */
void Bullet::update(float time) {
    // Move bullet in the specified direction
    rect.left += speed * time * (direction ? 1 : -1);

    // Check for collision with grass tiles
    int i = rect.top / 32;
    int j = rect.left / 32;

    if (TileMap[i][j] == 'B') {
        isAlive = false;
    }

    // Check if bullet is out of screen bounds
    if (rect.left < 0 || rect.left > W * 32) {
        isAlive = false;
    }
}
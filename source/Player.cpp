/*!
 * @file Player.cpp
 * @brief Player class implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Player
 * @brief Implementation of player character functionality
 */

#include "Player.h"
#include "Gameplay_objects/Tilemap.h"
#include "Constants.h" 

/*!
 * @brief Constructs a Player object with initial position and weapon
 * @param image Texture for the player sprite
 * @param startingWeapon Initial weapon for the player
 */
Player::Player(sf::Texture& image, Weapon* startingWeapon)
    : Entity(image, 7*32, 9*32, 40, 50),
      coins(0),
      onGround(false),
      currentFrame(0),
      lastAction(true),
      currentWeapon(startingWeapon),
      health(100), 
      maxHealth(100),
      invincibilityTime(0),
      speedMultiplier(1.0f),
      speedBoostTime(0),
      isSpeedBoosted(false),
      isInvincible(false),
      respawnX(7*32),
      respawnY(9*32) {
    sprite.setPosition(rect.left, rect.top);
}

/*!
 * @brief Adds coins to the player's collection
 * @param amount Number of coins to add
 */
void Player::addCoins(int amount) {
    coins += amount;
}

/*!
 * @brief Applies damage to the player if not invincible
 * @param damage Amount of damage to apply
 * 
 * If health reaches zero, the player respawns. After taking damage,
 * the player becomes temporarily invincible.
 */
void Player::takeDamage(int damage) {
    if(!isInvincible) {
        health -= damage;
        std::cout << "damage was taken!!!!!!!!!!!!!!!\n";
        if(health < 0) health = 0;
        if (health == 0) {
            respawn();
        }
        invincibilityTime = 1500.0f;
        isInvincible = true;
    }
}

/*!
 * @brief Switches the player's current weapon
 * @param newWeapon Weapon to switch to
 */
void Player::switchWeapon(Weapon* newWeapon) {
    currentWeapon = newWeapon;
}

/*!
 * @brief Updates the player's state each frame
 * @param time Time elapsed since last update in milliseconds
 * 
 * Handles movement, gravity, animation, and power-up timers.
 */
void Player::update(float time) {
    // Update speed boost timer
    if(isSpeedBoosted) {
        speedBoostTime -= time;
        if(speedBoostTime <= 0) {
            speedMultiplier = 1.0f;
            isSpeedBoosted = false;
        }
    }
    
    // Update invincibility timer
    if(isInvincible) {
        invincibilityTime -= time;
        if(invincibilityTime <= 0) {
            isInvincible = false;
        }
    }
    
    // Horizontal movement and collision
    rect.left += dx * time;
    Collision(0);

    // Vertical movement with gravity
    if (!onGround) dy += 0.0005 * time;
    rect.top += dy * time;
    onGround = false;
    Collision(1);

    // Animation frames
    currentFrame += 0.005 * time;
    idleFrame = currentFrame / 1.5;

    if (currentFrame > 6) currentFrame -= 6;
    if (idleFrame > 3) idleFrame -= 3;

    // Set sprite texture based on movement direction
    if (dx > 0) {
        sprite.setTextureRect(sf::IntRect(40 * int(currentFrame), 244, 40, 50));
        lastAction = true;
    } 
    else if (dx < 0) {
        sprite.setTextureRect(sf::IntRect(40 * int(currentFrame) + 40, 244, -40, 50));
        lastAction = false;
    } 
    else {
        // Idle animation
        if (lastAction) {
            sprite.setTextureRect(sf::IntRect(43 * int(idleFrame) + 4, 188, 40, 50));
        } else {
            sprite.setTextureRect(sf::IntRect(43 * int(idleFrame) + 4 + 40, 188, -40, 50));
        }
    }

    sprite.setPosition(rect.left, rect.top);

    // Update weapon
    if (currentWeapon) {
        currentWeapon->update(time);
    }
    dx = 0;
}

/*!
 * @brief Handles collision detection with tiles
 * @param dir Direction of collision (0 = horizontal, 1 = vertical)
 * 
 * Checks collision with various tile types and adjusts player position accordingly.
 * Special tile 'Z' triggers respawn with full health.
 */
void Player::Collision(int dir) {
    for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
        if (i < 0 || i >= H) continue;
        
        for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
            if (j < 0 || j >= W) continue;
            
            if (TileMap[i][j] == 'B' || TileMap[i][j] == 'G' || TileMap[i][j] == 'W' || TileMap[i][j] == 'Z') {
                if (TileMap[i][j] == 'Z') {
                    health = 100;
                    respawn();
                }
                if ((dx > 0) && (dir == 0)) rect.left = j * 32 - rect.width;
                if ((dx < 0) && (dir == 0)) rect.left = j * 32 + 32;
                if ((dy > 0) && (dir == 1)) { 
                    rect.top = i * 32 - rect.height; 
                    dy = 0; 
                    onGround = true; 
                }
                if ((dy < 0) && (dir == 1)) { 
                    rect.top = i * 32 + 32; 
                    dy = 0; 
                }
            }
            if (TileMap[i][j] == '0') TileMap[i][j] = ' ';
        }
    }
}

/*!
 * @brief Respawns the player at the respawn point
 * 
 * Resets health, position, and status effects. Grants temporary invincibility after respawn.
 */
void Player::respawn() {
    health = maxHealth;
    rect.left = respawnX;
    rect.top = respawnY;
    sprite.setPosition(respawnX, respawnY);
    dx = 0;
    dy = 0;
    speedMultiplier = 1.0f;
    speedBoostTime = 0;
    isSpeedBoosted = false;
    isInvincible = true;
    invincibilityTime = 1500.0f;
}

/*!
 * @brief Sets the player's respawn point
 * @param x X coordinate of respawn point
 * @param y Y coordinate of respawn point
 */
void Player::setRespawnPoint(float x, float y) {
    respawnX = x;
    respawnY = y;
}

/*!
 * @brief Sets the player's position and handles collision after movement
 * @param x X coordinate
 * @param y Y coordinate
 */
void Player::setPosition(float x, float y) {
    rect.left = x;
    rect.top = y;
    sprite.setPosition(x, y);
    
    dx = 0;
    dy = 0;
    onGround = false;
    
    Collision(0);
    Collision(1); 
    
    sprite.setPosition(rect.left, rect.top);
}
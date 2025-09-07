/*!
 * @file Player.h
 * @brief Player class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Player
 * @brief Represents the player character in the game
 * 
 * Inherits from Entity and contains player-specific properties and behaviors
 * including health management, weapon handling, and movement.
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Weapons/Weapon.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Player : public Entity {
public:
    int coins;                      ///< Number of coins collected by the player
    bool onGround;                  ///< Indicates if the player is on ground
    float currentFrame;             ///< Current animation frame
    float idleFrame;                ///< Idle animation frame
    bool lastAction;                ///< Last action performed (for animation)
    Weapon* currentWeapon;          ///< Currently equipped weapon
    
    int health;                     ///< Current health points
    int maxHealth;                  ///< Maximum health points
    float invincibilityTime;        ///< Remaining invincibility time
    float speedMultiplier;          ///< Current speed multiplier
    float speedBoostTime;           ///< Remaining speed boost time
    bool isSpeedBoosted;            ///< Speed boost status
    bool isInvincible;              ///< Invincibility status

    float respawnX;                 ///< X coordinate of respawn point
    float respawnY;                 ///< Y coordinate of respawn point

    /*!
     * @brief Constructs a Player object
     * @param image Texture for the player sprite
     * @param startingWeapon Initial weapon for the player
     */
    Player(sf::Texture& image, Weapon* startingWeapon);
    
    /*!
     * @brief Adds coins to the player's collection
     * @param amount Number of coins to add
     */
    void addCoins(int amount);
    
    /*!
     * @brief Applies damage to the player
     * @param damage Amount of damage to apply
     */
    void takeDamage(int damage);
    
    /*!
     * @brief Switches the player's current weapon
     * @param newWeapon Weapon to switch to
     */
    void switchWeapon(Weapon* newWeapon);
    
    /*!
     * @brief Updates the player's state
     * @param time Time elapsed since last update
     */
    void update(float time) override;
    
    /*!
     * @brief Handles collision detection and response
     * @param dir Direction of collision (0 = horizontal, 1 = vertical)
     */
    void Collision(int dir);
    
    /*!
     * @brief Respawns the player at the respawn point
     */
    void respawn();
    
    /*!
     * @brief Sets the player's respawn point
     * @param x X coordinate of respawn point
     * @param y Y coordinate of respawn point
     */
    void setRespawnPoint(float x, float y); 
    
    /*!
     * @brief Sets the player's position
     * @param x X coordinate
     * @param y Y coordinate
     */
    void setPosition(float x, float y); 
};

#endif
/*!
 * @file Constants.h
 * @brief Game constants and configuration parameters
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @defgroup Constants Game Constants
 * @brief Collection of all game constants and configuration values
 * 
 * This file contains all tunable parameters and constants used throughout the game.
 * Constants are organized by category for easy maintenance and balancing.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

// Time management
constexpr float TIME_DIVISOR = 700.0f;   ///< Divisor for normalizing time calculations
constexpr float MAX_TIME = 20.0f;        ///< Maximum allowed time per frame (prevents extreme values)

// Player movement
constexpr float BASE_MOVE_SPEED = 0.1f;          ///< Base movement speed for the player
constexpr float JUMP_SPEED = -0.35f;             ///< Initial vertical velocity when jumping
constexpr float SPEED_BOOST_MULTIPLIER = 1.25f;  ///< Speed multiplier when boosted

// Combat
constexpr int DAMAGE_ON_ENEMY_COLLISION = 20;    ///< Damage taken when colliding with an enemy
constexpr float BULLET_X_OFFSET_ACTION = 40.0f;  ///< X offset for bullets when facing right
constexpr float BULLET_X_OFFSET_DEFAULT = -10.0f;///< X offset for bullets when facing left
constexpr float BULLET_Y_OFFSET = 10.0f;         ///< Y offset for bullet spawning

// Power-ups
constexpr int COIN_VALUE = 1;                    ///< Points added per coin collected
constexpr int HEAL_AMOUNT = 35;                  ///< Health restored by medkits
constexpr float INVINCIBILITY_DURATION = 5000.0f;///< Duration of invincibility power-up (ms)
constexpr float SPEED_BOOST_DURATION = 10000.0f; ///< Duration of speed boost power-up (ms)

// Platform collision
constexpr float COLLISION_THRESHOLD = 10.0f;     ///< Maximum overlap for platform collision detection

// Graphics
constexpr int TILE_SIZE = 32;                    ///< Size of each tile in pixels
constexpr float CAMERA_Y_OFFSET = 70.0f;         ///< Vertical offset for camera positioning

// Tilemap symbols
constexpr char TILE_GRASS = 'B';                 ///< Tile symbol for grass blocks
constexpr char TILE_GROUND = 'G';                ///< Tile symbol for ground blocks
constexpr char TILE_BRICK = 'Z';                 ///< Tile symbol for brick blocks
constexpr char TILE_EMPTY = ' ';                 ///< Tile symbol for empty space

#endif // CONSTANTS_H
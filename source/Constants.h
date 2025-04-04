#ifndef CONSTANTS_H
#define CONSTANTS_H

// Time management
constexpr float TIME_DIVISOR = 700.0f;
constexpr float MAX_TIME = 20.0f;

// Player movement
constexpr float BASE_MOVE_SPEED = 0.1f;
constexpr float JUMP_SPEED = -0.35f;
constexpr float SPEED_BOOST_MULTIPLIER = 1.25f;

// Combat
constexpr int DAMAGE_ON_ENEMY_COLLISION = 20;
constexpr float BULLET_X_OFFSET_ACTION = 40.0f;
constexpr float BULLET_X_OFFSET_DEFAULT = -10.0f;
constexpr float BULLET_Y_OFFSET = 10.0f;

// Power-ups
constexpr int COIN_VALUE = 1;
constexpr int HEAL_AMOUNT = 35;
constexpr float INVINCIBILITY_DURATION = 5000.0f;
constexpr float SPEED_BOOST_DURATION = 10000.0f;

// Platform collision
constexpr float COLLISION_THRESHOLD = 10.0f;

// Graphics
constexpr int TILE_SIZE = 32;
constexpr float CAMERA_Y_OFFSET = 70.0f;

// Tilemap symbols
constexpr char TILE_SOLID = 'B';
constexpr char TILE_EMPTY = ' ';

#endif // CONSTANTS_H
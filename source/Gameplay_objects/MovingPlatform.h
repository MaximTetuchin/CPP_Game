/*!
 * @file MovingPlatform.h
 * @brief MovingPlatform class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class MovingPlatform
 * @brief Platform that moves horizontally between defined boundaries
 * @ingroup GameplayObjects
 * 
 * Inherits from Entity and represents a platform that moves left and right
 * within a specified range. Provides dynamic movement for gameplay variety.
 */

#ifndef MOVING_PLATFORM_H
#define MOVING_PLATFORM_H
#include "../Entity.h"

class MovingPlatform : public Entity {
private:
    float moveRange;    ///< Maximum horizontal movement range from start position
    float startX;       ///< Initial X coordinate (reference point for movement)
    float speed;        ///< Movement speed in pixels per millisecond
    bool movingRight;   ///< Current movement direction (true = right, false = left)

public:
    /*!
     * @brief Constructs a MovingPlatform object
     * @param image Texture for the platform sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     * @param w Width of the platform
     * @param h Height of the platform
     * @param range Maximum horizontal movement range from start position
     * @param spd Movement speed in pixels per millisecond
     */
    MovingPlatform(sf::Texture &image, float x, float y, float w, float h, float range, float spd);
    
    /*!
     * @brief Updates the platform's horizontal movement
     * @param time Time elapsed since last update
     * 
     * Moves the platform horizontally within its defined range and
     * reverses direction when reaching movement boundaries.
     */
    void update(float time) override;
};

#endif
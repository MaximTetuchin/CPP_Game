/*!
 * @file VerticalMovingPlatform.h
 * @brief VerticalMovingPlatform class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class VerticalMovingPlatform
 * @brief Platform that moves vertically between defined boundaries
 * @ingroup GameplayObjects
 * 
 * Inherits from Entity and represents a platform that moves up and down
 * within a specified range. Provides dynamic movement for gameplay variety.
 */

#ifndef VERTICAL_MOVING_PLATFORM
#define VERTICAL_MOVING_PLATFORM
#include "../Entity.h"

class VerticalMovingPlatform : public Entity {
private:
    float moveRange;    ///< Maximum vertical movement range from start position
    float startY;       ///< Initial Y coordinate (reference point for movement)
    float speed;        ///< Movement speed in pixels per millisecond
    bool movingDown;    ///< Current movement direction (true = down, false = up)

public:
    /*!
     * @brief Constructs a VerticalMovingPlatform object
     * @param image Texture for the platform sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     * @param w Width of the platform
     * @param h Height of the platform
     * @param range Maximum vertical movement range from start position
     * @param spd Movement speed in pixels per millisecond
     */
    VerticalMovingPlatform(sf::Texture& image, float x, float y, float w, float h, float range, float spd);
    
    /*!
     * @brief Updates the platform's vertical movement
     * @param time Time elapsed since last update
     * 
     * Moves the platform vertically within its defined range and
     * reverses direction when reaching movement boundaries.
     */
    void update(float time) override;
};

#endif
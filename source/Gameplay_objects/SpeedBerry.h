/*!
 * @file SpeedBerry.h
 * @brief SpeedBerry class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class SpeedBerry
 * @brief Collectible item that grants temporary speed boost
 * @ingroup GameplayObjects
 * 
 * Inherits from Entity and represents a speed berry power-up that
 * temporarily increases the player's movement speed when collected.
 */

#ifndef SPEED_BERRY_H
#define SPEED_BERRY_H
#include "../Entity.h"

class SpeedBerry : public Entity {
public:
    /*!
     * @brief Constructs a SpeedBerry object
     * @param image Texture for the speed berry sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     */
    SpeedBerry(sf::Texture& image, float x, float y);
    
    /*!
     * @brief Updates the speed berry's state
     * @param time Time elapsed since last update
     * 
     * Currently handles basic entity updates. Collision detection
     * with the player is handled in the main game loop.
     */
    void update(float time) override;
};

#endif
/*!
 * @file WinBlock.h
 * @brief WinBlock class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class WinBlock
 * @brief Special entity that triggers win condition when touched by player
 * @ingroup GameplayObjects
 * 
 * Inherits from Entity and represents the goal or finish area of a level.
 * When the player collides with this block, the game win condition is triggered.
 */

#ifndef WINBLOCK_H
#define WINBLOCK_H
#include "../Entity.h"

class WinBlock : public Entity {
public:
    /*!
     * @brief Constructs a WinBlock object
     * @param image Texture for the win block sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     */
    WinBlock(sf::Texture& image, float x, float y);
    
    /*!
     * @brief Updates the win block's state
     * @param time Time elapsed since last update
     * 
     * Currently handles basic entity updates. Collision detection
     * with the player is handled in the main game loop.
     */
    void update(float time) override;
};

#endif
/*!
 * @file Coin.h
 * @brief Coin class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Coin
 * @brief Collectible currency item that increases player's coin count
 * @ingroup GameplayObjects
 * 
 * Inherits from Entity and represents a coin collectible that
 * increases the player's coin counter when collected.
 */

#ifndef COIN_H
#define COIN_H

#include "../Entity.h"

class Coin : public Entity {
public:
    /*!
     * @brief Constructs a Coin object
     * @param image Texture for the coin sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     */
    Coin(sf::Texture &image, float x, float y);
    
    /*!
     * @brief Updates the coin's state
     * @param time Time elapsed since last update
     * 
     * Currently handles basic entity updates. Collision detection
     * with the player is handled in the main game loop.
     */
    void update(float time) override;
};

#endif
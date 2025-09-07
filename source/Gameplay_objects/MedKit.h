/*!
 * @file MedKit.h
 * @brief MedKit class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class MedKit
 * @brief Collectible item that restores player health
 * @ingroup GameplayObjects
 * 
 * Inherits from Entity and represents a medical kit power-up that
 * restores a portion of the player's health when collected.
 */

#ifndef MED_KIT_H
#define MED_KIT_H
#include "../Entity.h"

class MedKit : public Entity {
public:
    /*!
     * @brief Constructs a MedKit object
     * @param image Texture for the medkit sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     */
    MedKit(sf::Texture& image, float x, float y);
    
    /*!
     * @brief Updates the medkit's state
     * @param time Time elapsed since last update
     * 
     * Currently handles basic entity updates. Collision detection
     * with the player is handled in the main game loop.
     */
    void update(float time) override;
};

#endif
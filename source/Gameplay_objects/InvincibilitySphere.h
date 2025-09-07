/*!
 * @file InvincibilitySphere.h
 * @brief InvincibilitySphere class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class InvincibilitySphere
 * @brief Collectible item that grants temporary invincibility
 * @ingroup GameplayObjects
 * 
 * Inherits from Entity and represents an invincibility sphere power-up that
 * grants the player temporary invincibility when collected.
 */

#ifndef INVINCIBILITY_SPHERE_H
#define INVINCIBILITY_SPHERE_H
#include "../Entity.h"

class InvincibilitySphere : public Entity {
public:
    /*!
     * @brief Constructs an InvincibilitySphere object
     * @param image Texture for the invincibility sphere sprite
     * @param x Initial X coordinate position
     * @param y Initial Y coordinate position
     */
    InvincibilitySphere(sf::Texture& image, float x, float y);
    
    /*!
     * @brief Updates the invincibility sphere's state
     * @param time Time elapsed since last update
     * 
     * Currently handles basic entity updates. Collision detection
     * with the player is handled in the main game loop.
     */
    void update(float time) override;
};

#endif
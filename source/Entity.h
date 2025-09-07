/*!
 * @file Entity.h
 * @brief Entity base class definition
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @class Entity
 * @brief Base class for all game entities
 * @ingroup Entities
 * 
 * Provides common functionality for all game objects including
 * rendering, positioning, and basic physics properties.
 */

#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity {
public:
    sf::Sprite sprite;          ///< SFML sprite for visual representation
    sf::FloatRect rect;         ///< Bounding rectangle for collision detection
    float dx;                   ///< Horizontal velocity
    float dy;                   ///< Vertical velocity
    bool isAlive;               ///< Entity's alive status
    
    /*!
     * @brief Constructs an Entity object
     * @param image Texture for the entity sprite
     * @param x Initial X coordinate
     * @param y Initial Y coordinate
     * @param w Width of the entity
     * @param h Height of the entity
     */
    Entity(sf::Texture &image, float x, float y, float w, float h);
    
    /*!
     * @brief Virtual destructor for proper cleanup of derived classes
     */
    virtual ~Entity() = default;
    
    /*!
     * @brief Pure virtual update method to be implemented by derived classes
     * @param time Time elapsed since last update
     */
    virtual void update(float time) = 0;
    
    /*!
     * @brief Draws the entity to the specified window
     * @param window Reference to the SFML render window
     */
    virtual void draw(sf::RenderWindow &window);
};

#endif
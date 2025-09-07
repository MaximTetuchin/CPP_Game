/*!
 * @file Tilemap.h
 * @brief Tilemap configuration and declarations
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @defgroup LevelDesign Level Design
 * @brief Tilemap and level configuration data
 * 
 * Contains level dimensions and tilemap data for game world construction.
 * The tilemap uses character-based representation for different tile types.
 */

#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>

const int H = 25; ///< Map height in tiles
const int W = 60; ///< Map width in tiles

/*!
 * @brief External declaration of the tilemap array
 * 
 * The tilemap is defined in Tilemap.cpp and uses character codes to represent
 * different tile types. Common tile symbols include:
 * - ' ' : Empty space
 * - 'B' : Grass block
 * - 'G' : Ground block  
 * - 'Z' : Brick block
 * - 'E' : Walking enemy spawn
 * - 'F' : Flying enemy spawn
 * - 'J' : Jumping enemy spawn
 * - 'C' : Coin
 * - 'H' : Medkit
 * - 'I' : Invincibility sphere
 * - 'S' : Speed berry
 * - 'Q' : Win block
 * - 'L' : Moving platform
 * - 'U' : Vertical moving platform
 */
extern sf::String TileMap[H];

#endif
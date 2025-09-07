/*!
 * @file Tilemap.cpp
 * @brief Tilemap data implementation
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * 
 * @ingroup LevelDesign
 * 
 * Contains the actual tilemap data for the game level. The tilemap uses
 * character-based representation where each character corresponds to
 * a specific game object or tile type.
 */

#include "Tilemap.h"

/*!
 * @brief Tilemap array defining the game level layout
 * 
 * The tilemap uses a character-based system where each character represents
 * a specific game element. The map is H (25) rows high and W (60) columns wide.
 * Empty spaces are represented by spaces or incomplete rows are automatically
 * filled with empty tiles.
 * 
 * @note The map uses fixed-width formatting for visual clarity in code.
 */
sf::String TileMap[H] = {
    "W                                                          W",
    "W                                                          W",
    "W        H                                                 W",
    "W        B                                                 W",
    "W        G  J          S       S                     V     W",
    "W        GBBBBBBB      B       BB       L    L             W",
    "W                                                          W",
    "W             F                                            W",
    "W                       C   U                    V         W",
    "W                        B                                 W",
    "W                      I                 F                 W",
    "W          E    B   J  B    M                              W",
    "BBBBBBBBBBBBBBBBGBBBBBBBBBBBBBBBBBBBB                  QQQQB",
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGZZZZZZZZZZZZZZZZZZGGGGG",
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGZZZZZZZZZZZZZZZZZZGGGGG",
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG                  GGGGG", 
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG                  GGGGG",
};

// Tile Symbol Reference:
// B - Grass tile                      E - WalkingEnemy
// G - Ground tile                     Z - KillBlock (instant death)
// L - Left/right moving platform      F - FlyingEnemy  
// U - Up/down moving platform         J - JumpingEnemy
// C - Coin                            D - ArmoredWalkingEnemy
// H - Medkit                          V - ArmoredFlyingEnemy
// I - InvincibilitySphere             M - ArmoredJumpingEnemy
// S - SpeedBerry                      Q - WinBlock (level completion)
// W - (Unused in comments, appears to be boundary walls)
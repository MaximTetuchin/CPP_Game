#include "Tilemap.h"

sf::String TileMap[H] = {
    "W                                                          W",
    "W                                                          W",
    "W                                                          W",
    "W                                                          W",
    "W                                                          W",
    "W                                                          W",
    "W                                                          W",
    "W                                                          W",
    "W                                                          W",
    "W                                                          W",
    "W                                                          W",
    "W                                                          W",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG", 
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
};
// B - Grass tile,                       E - WalkingEnemy
// G - Ground tile
// L - lefr/right moving platform,       F - FlyingEnemy
// U - Up/down moving platform,          J - JumpingEnemy
// C - Coin,                             D - ArmoredWalkingEnemy
// H - Med.kit,                          V - ArmoredFlyingEnemy
// I - InvincibilitySphere,              M - ArmoredJumpingEnemy
// S - SpeedBerry                      
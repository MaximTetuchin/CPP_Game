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
    "W        B                                                 W",
    "BBBBBBBBBGBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG", 
    "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG",
};
// B - Grass tile,                       E - WalkingEnemy
// G - Ground tile                       Z - Brick
// L - lefr/right moving platform,       F - FlyingEnemy
// U - Up/down moving platform,          J - JumpingEnemy
// C - Coin,                             D - ArmoredWalkingEnemy
// H - Med.kit,                          V - ArmoredFlyingEnemy
// I - InvincibilitySphere,              M - ArmoredJumpingEnemy
// S - SpeedBerry                      
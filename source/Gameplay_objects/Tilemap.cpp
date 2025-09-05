/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "Tilemap.h"

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
// B - Grass tile,                       E - WalkingEnemy
// G - Ground tile                       Z - KillBlock
// L - lefr/right moving platform,       F - FlyingEnemy
// U - Up/down moving platform,          J - JumpingEnemy
// C - Coin,                             D - ArmoredWalkingEnemy
// H - Med.kit,                          V - ArmoredFlyingEnemy
// I - InvincibilitySphere,              M - ArmoredJumpingEnemy
// S - SpeedBerry                      
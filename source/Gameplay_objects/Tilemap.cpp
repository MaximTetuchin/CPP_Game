#include "Tilemap.h"

sf::String TileMap[H] = {
    "                                             ",
    "B                                H          B",
    "B                                B          B",
    "B                 V                         B",
    "B          C                                B",
    "B         BBBB         BBBBBBBBBBB          B",
    "B                                B          B",
    "BBB                              BI         B",
    "B       L                        BB         B",
    "B                    U    J                 B",
    "B    B                    BB    S      D    B", 
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};
// B - default black tile,               E - WalkingEnemy
// L - lefr/right moving platform,       F - FlyingEnemy
// U - Up/down moving platform,          J - JumpingEnemy
// C - Coin,                             D - ArmoredWalkingEnemy
// H - Med.kit,                          V - ArmoredFlyingEnemy
// I - InvincibilitySphere,              M - ArmoredJumpingEnemy
// S - SpeedBerry
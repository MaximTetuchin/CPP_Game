#include "Tilemap.h"

sf::String TileMap[H] = {
    "B                                                          B"
    "B                                                          B"
    "B                                                          B"
    "B                                                          B",
    "B                                                          B",
    "B                                                          B",
    "B                 V                                        B",
    "B          C                   H      V        C           B",
    "B        BBBBB         BBBBBBBBBBB            BBBB         B",
    "B                                                          B",
    "BBBB                 U           I              D          B",
    "B          F                     BB      BBBBBBBBBBB       B",
    "B                        J                                 B",
    "B    C     B      B  J    BB    S      D           D       B", 
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};
// B - default black tile,               E - WalkingEnemy
// L - lefr/right moving platform,       F - FlyingEnemy
// U - Up/down moving platform,          J - JumpingEnemy
// C - Coin,                             D - ArmoredWalkingEnemy
// H - Med.kit,                          V - ArmoredFlyingEnemy
// I - InvincibilitySphere,              M - ArmoredJumpingEnemy
// S - SpeedBerry
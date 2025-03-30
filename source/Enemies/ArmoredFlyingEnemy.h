#ifndef ARMORED_FLYING_ENEMY_H
#define ARMORED_FLYING_ENEMY_H
#include "FlyingEnemy.h"

class ArmoredFlyingEnemy : public FlyingEnemy {
public:
    ArmoredFlyingEnemy(sf::Texture& image, float x, float y, float w, float h, 
                      float speed, float range);
};
#endif
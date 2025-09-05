/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#ifndef ARMORED_WALKING_ENEMY_H
#define ARMORED_WALKING_ENEMY_H
#include "WalkingEnemy.h"

class ArmoredWalkingEnemy : public WalkingEnemy {
public:
    ArmoredWalkingEnemy(sf::Texture &image, float x, float y, float w, float h,
                      float speed, float range);
};

#endif
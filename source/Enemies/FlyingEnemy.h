/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#ifndef FLYING_ENEMY_H
#define FLYING_ENEMY_H
#include "Enemy.h"

class FlyingEnemy : public Enemy {
public:
    FlyingEnemy(sf::Texture &image, float x, float y, float w, float h, 
               float speed, float range);

    void update(float time) override;
    void Collision(int dir) override;
};
#endif
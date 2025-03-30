#ifndef WALKING_ENEMY_H
#define WALKING_ENEMY_H

#include "Enemy.h"

class WalkingEnemy : public Enemy {
public:
    bool onGround;
    
    WalkingEnemy(sf::Texture &image, float x, float y, float w, float h, 
                float speed, float range);
    
    void update(float time) override;
    void Collision(int dir) override;
};

#endif
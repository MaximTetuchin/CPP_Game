#ifndef ENEMY_H
#define ENEMY_H
#include "../Entity.h"


class Enemy : public Entity {
public:
    int armor;
    int health;
    float speed;
    float moveRange;
    float startX;
    bool isAlive;

    Enemy(sf::Texture &image, float x, float y, float w, float h, 
          int armor, float speed, float range);
    
    virtual void takeDamage(int damage);
    virtual void update(float time) = 0;
    virtual void Collision(int dir) = 0;
};
#endif
/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#ifndef BULLET_H
#define BULLET_H
#include "../Entity.h"

class Bullet : public Entity {
public:
    bool direction; // true = right, false = left
    float speed; 
    int damage;

    Bullet(sf::Texture& image, float x, float y, bool dir, float spd, int dmg);
    void update(float time) override;
};

#endif
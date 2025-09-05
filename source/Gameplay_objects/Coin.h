/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#ifndef COIN_H
#define COIN_H

#include "../Entity.h"

class Coin : public Entity {
public:
    Coin(sf::Texture &image, float x, float y);
    void update(float time) override;
};

#endif

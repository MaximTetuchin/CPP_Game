#ifndef COIN_H
#define COIN_H

#include "../Entity.h"

class Coin : public Entity {
public:
    Coin(sf::Texture &image, float x, float y);
    void update(float time) override;
};

#endif

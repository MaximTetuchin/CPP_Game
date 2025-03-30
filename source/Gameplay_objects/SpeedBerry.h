#ifndef SPEED_BERRY_H
#define SPEED_BERRY_H
#include "../Entity.h"

class SpeedBerry : public Entity {
    public:
        SpeedBerry(sf::Texture& image, float x, float y);
        void update(float time) override;
    };
#endif
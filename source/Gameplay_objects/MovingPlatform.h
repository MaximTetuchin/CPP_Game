#ifndef MOVING_PLATFORM_H
#define MOVING_PLATFORM_H
#include "../Entity.h"
class MovingPlatform : public Entity {
    private:
        float moveRange;
        float startX;
        float speed;
        bool movingRight;
    
    public:
        MovingPlatform(sf::Texture &image, float x, float y, float w, float h, float range, float spd);
        void update(float time) override;
    };
#endif
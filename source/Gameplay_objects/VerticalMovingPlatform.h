#ifndef VERTICAL_MOVING_PLATFORM
#define VERTICAL_MOVING_PLATFORM
#include "../Entity.h"

class VerticalMovingPlatform : public Entity {
    private:
        float moveRange;
        float startY;
        float speed;
        bool movingDown;
    
    public:
        VerticalMovingPlatform(sf::Texture& image, float x, float y, float w, float h, float range, float spd);
        void update(float time) override;
    };

#endif
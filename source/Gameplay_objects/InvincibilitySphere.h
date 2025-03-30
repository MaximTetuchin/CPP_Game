#ifndef INVINCIBILITY_SPHERE_H
#define INVINCIBILITY_SPHERE_H
#include "../Entity.h"

class InvincibilitySphere : public Entity {
    public:
        InvincibilitySphere(sf::Texture& image, float x, float y);
        void update(float time) override;
    };
#endif
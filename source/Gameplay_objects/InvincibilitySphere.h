/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#ifndef INVINCIBILITY_SPHERE_H
#define INVINCIBILITY_SPHERE_H
#include "../Entity.h"

class InvincibilitySphere : public Entity {
    public:
        InvincibilitySphere(sf::Texture& image, float x, float y);
        void update(float time) override;
    };
#endif
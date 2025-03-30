#ifndef WEAPON_H
#define WEAPON_H
#include <vector>
#include <memory>
#include "../Entity.h"

class Weapon {
    public:
        virtual ~Weapon() = default;
        virtual bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) = 0;
        virtual void update(float time) = 0;
        virtual void setBulletTexture(sf::Texture& texture) = 0;
        virtual std::string getName() const = 0;
    };
#endif
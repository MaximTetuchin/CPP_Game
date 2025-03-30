#ifndef RIFLE_H
#define RIFLE_H

#include "Weapon.h"
class Rifle : public Weapon {
private:
    float fireDelay;
    float currentDelay;
    sf::Texture bulletTexture;
    int damage;

public:
    Rifle(float delay = 200.0f, int dmg = 18);
    void setBulletTexture(sf::Texture& texture) override;
    bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) override;
    void update(float time) override;
    std::string getName() const override;
};
#endif
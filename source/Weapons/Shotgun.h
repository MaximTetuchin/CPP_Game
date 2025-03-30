#ifndef SHOTGUN_H
#define SHOTHUN_H

#include "Weapon.h"
class Shotgun : public Weapon {
private:
    float fireDelay;
    float currentDelay;
    sf::Texture bulletTexture;
    int damage;
    int pelletCount;

public:
    Shotgun(float delay = 2000.0f, int dmg = 55, int pellets = 2);
    
    void setBulletTexture(sf::Texture& texture) override;
    std::string getName() const override;
    bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) override;
    void update(float time) override;
};

#endif
#ifndef MINIGUN_H
#define MINIGUN_H
#include "Weapon.h"

class Minigun : public Weapon {
private:
    float fireDelay;
    float currentDelay;
    sf::Texture bulletTexture;
    int damage;
    int bulletsPerShot;

public:
    Minigun(float delay = 150.0f, int dmg = 11, int bullets = 3);
    
    void setBulletTexture(sf::Texture& texture) override;
    std::string getName() const override;
    bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) override;
    void update(float time) override;
};
#endif
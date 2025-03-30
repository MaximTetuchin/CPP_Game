#ifndef PISTOL_H
#define PISTOL_H
#include "Weapon.h"

class Pistol : public Weapon {
private:
    float fireDelay;
    float currentDelay;
    sf::Texture bulletTexture;
    int damage;

public:
    Pistol(float delay = 420.0f, int dmg = 25);
    
    void setBulletTexture(sf::Texture& texture) override;
    std::string getName() const override;
    bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) override;
    void update(float time) override;
};

#endif
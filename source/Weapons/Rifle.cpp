#include "Rifle.h"
#include "Bullet.h"

Rifle::Rifle(float delay, int dmg)
    : fireDelay(delay), currentDelay(0), damage(dmg) {}

void Rifle::setBulletTexture(sf::Texture& texture) {
    bulletTexture = texture;
}

bool Rifle::tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) {
    if (currentDelay <= 0) {
        bullets.push_back(new Bullet(bulletTexture,
            x + (direction ? 6 : -6),
            y + 6,
            direction,
            0.7f,
            damage));
        currentDelay = fireDelay;
        return true;
    }
    return false;
}

void Rifle::update(float time) {
    if (currentDelay > 0) currentDelay -= time;
}

std::string Rifle::getName() const {
    return "Rifle";
}
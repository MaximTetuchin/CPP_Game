#include "Pistol.h"
#include "Bullet.h" // Если Bullet — ваш класс пули

Pistol::Pistol(float delay, int dmg)
    : fireDelay(delay), currentDelay(0), damage(dmg) {}

void Pistol::setBulletTexture(sf::Texture& texture) {
    bulletTexture = texture;
}

std::string Pistol::getName() const {
    return "Pistol";
}

bool Pistol::tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) {
    if (currentDelay <= 0) {
        bullets.push_back(new Bullet(bulletTexture,
            x + (direction ? 6 : -6),
            y + 6,
            direction,
            0.5f,
            damage));
        currentDelay = fireDelay;
        return true;
    }
    return false;
}

void Pistol::update(float time) {
    if (currentDelay > 0) currentDelay -= time;
}
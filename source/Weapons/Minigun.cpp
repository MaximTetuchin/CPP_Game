/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "Minigun.h"
#include "Bullet.h"

Minigun::Minigun(float delay, int dmg, int bullets)
    : fireDelay(delay), currentDelay(0), damage(dmg), bulletsPerShot(bullets) {}

void Minigun::setBulletTexture(sf::Texture& texture) {
    bulletTexture = texture;
}

std::string Minigun::getName() const {
    return "Minigun";
}

bool Minigun::tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) {
    if (currentDelay <= 0) {
        for (int i = 0; i < bulletsPerShot; i++) {
            bullets.push_back(new Bullet(bulletTexture,
                x + (direction ? 6 : -6),
                y + 6 + (i * 3),
                direction,
                0.5f + (i * 0.1f),
                damage));
        }
        currentDelay = fireDelay;
        return true;
    }
    return false;
}

void Minigun::update(float time) {
    if (currentDelay > 0) currentDelay -= time;
}
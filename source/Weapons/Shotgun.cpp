/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "Shotgun.h"
#include "Bullet.h"

Shotgun::Shotgun(float delay, int dmg, int pellets)
    : fireDelay(delay), currentDelay(0), damage(dmg), pelletCount(pellets) {}

void Shotgun::setBulletTexture(sf::Texture& texture) {
    bulletTexture = texture;
}

std::string Shotgun::getName() const {
    return "Shotgun";
}

bool Shotgun::tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) {
    if (currentDelay <= 0) {
        for (int i = 0; i < pelletCount; i++) {
            bullets.push_back(new Bullet(bulletTexture,
                x + (direction ? 6 : -6),
                y + 6 + (i * 5),
                direction,
                0.5f + (i * 0.1f),
                damage));
        }
        currentDelay = fireDelay;
        return true;
    }
    return false;
}

void Shotgun::update(float time) {
    if (currentDelay > 0) currentDelay -= time;
}
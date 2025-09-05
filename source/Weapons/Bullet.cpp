/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "Bullet.h"
#include "../Gameplay_objects/Tilemap.h"

Bullet::Bullet(sf::Texture& image, float x, float y, bool dir, float spd, int dmg)
    : Entity(image, x, y, 8, 8), direction(dir), speed(spd), damage(dmg) {
    sprite.setTextureRect(sf::IntRect(247, 583, 8, 8));
}

void Bullet::update(float time) {
    rect.left += speed * time * (direction ? 1 : -1);

    int i = rect.top / 32;
    int j = rect.left / 32;

    if (TileMap[i][j] == 'B') {
        isAlive = false;
    }

    if (rect.left < 0 || rect.left > W * 32) {
        isAlive = false;
    }
}
#include "FlyingEnemy.h"
#include "../Gameplay_objects/Tilemap.h"

FlyingEnemy::FlyingEnemy(sf::Texture &image, float x, float y, float w, float h,
                        float speed, float range)
    : Enemy(image, x, y, w, h, 0, speed, range) {
    sprite.setTextureRect(sf::IntRect(0, 0, 42, 42));
}

void FlyingEnemy::update(float time) {
    float nextX = rect.left + speed * time;

    if (nextX < startX - moveRange || nextX > startX + moveRange) {
        speed = -speed;
        nextX = rect.left + speed * time;
    }

    rect.left = nextX;
    Collision(0);
}

void FlyingEnemy::Collision(int dir) {
    if (dir == 0) {
        for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
            for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
                if (TileMap[i][j] == 'B') {
                    if (speed > 0) rect.left = j * 32 - rect.width;
                    else if (speed < 0) rect.left = j * 32 + 32;
                }
            }
        }
    }
}
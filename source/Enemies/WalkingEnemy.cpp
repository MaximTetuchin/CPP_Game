/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "WalkingEnemy.h"
#include "../Gameplay_objects/Tilemap.h"

WalkingEnemy::WalkingEnemy(sf::Texture &image, float x, float y, float w, float h,
                         float speed, float range)
    : Enemy(image, x, y, w, h, 0, speed, range), 
      onGround(false) {
    sprite.setTextureRect(sf::IntRect(0, 0, 34, 45));
}

void WalkingEnemy::update(float time) {
    float nextX = rect.left + speed * time;

    if (nextX < startX - moveRange || nextX > startX + moveRange) {
        speed = -speed;
        nextX = rect.left + speed * time;
    }

    rect.left = nextX;
    Collision(0);

    if(!onGround) dy += 0.0005 * time;
    rect.top += dy * time;
    onGround = false;
    Collision(1);
}

void WalkingEnemy::Collision(int dir) {
    for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
        for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
            if (TileMap[i][j] == 'B') {
                if ((speed > 0) && (dir == 0)) rect.left = j * 32 - rect.width;
                if ((speed < 0) && (dir == 0)) rect.left = j * 32 + 32;
                if ((dy > 0) && (dir == 1)) { 
                    rect.top = i * 32 - rect.height; 
                    dy = 0; 
                    onGround = true; 
                }
                if ((dy < 0) && (dir == 1)) { 
                    rect.top = i * 32 + 32; 
                    dy = 0; 
                }
            }
        }
}
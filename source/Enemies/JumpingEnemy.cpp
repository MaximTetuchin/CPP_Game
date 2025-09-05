/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "JumpingEnemy.h"

JumpingEnemy::JumpingEnemy(sf::Texture &image, float x, float y, float w, float h,
                          float speed, float range, float jumpForce)
    : WalkingEnemy(image, x, y, w, h, speed, range),
      jumpForce(jumpForce) {
    jumpInterval = rand() % 3000 + 2000;
    jumpTimer = jumpInterval;
    sprite.setTextureRect(sf::IntRect(0, 0, 39, 45)); 
}

void JumpingEnemy::update(float time) {
    jumpTimer -= time;
    
    if(jumpTimer <= 0 && onGround) {
        dy = -jumpForce;
        onGround = false;

        jumpInterval = rand() % 3000 + 2000;
        jumpTimer = jumpInterval;
    }

    WalkingEnemy::update(time);
}
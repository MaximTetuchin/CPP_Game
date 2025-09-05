/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "ArmoredJumpingEnemy.h"
ArmoredJumpingEnemy::ArmoredJumpingEnemy(sf::Texture &image, float x, float y, float w, float h,
                                        float speed, float range, float jumpForce)
    : JumpingEnemy(image, x, y, w, h, speed, range, jumpForce) {
    armor = 10;
    sprite.setTextureRect(sf::IntRect(0, 0, 39, 45));
}
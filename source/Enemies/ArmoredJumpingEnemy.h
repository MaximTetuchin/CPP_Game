/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#ifndef ARMORED_JUMPING_ENEMY_H
#define ARMORED_JUMPING_ENEMY_H
#include "JumpingEnemy.h"
class ArmoredJumpingEnemy : public JumpingEnemy {
public:
    ArmoredJumpingEnemy(sf::Texture &image, float x, float y, float w, float h,
                       float speed, float range, float jumpForce = 0.35f);
};
#endif
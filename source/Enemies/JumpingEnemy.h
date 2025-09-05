/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#ifndef JUMPING_ENEMY_H
#define JUMPING_ENEMY_H
#include "WalkingEnemy.h"
class JumpingEnemy : public WalkingEnemy {
    private:
        float jumpTimer;
        float jumpInterval;
        float jumpForce;
    
    public:
        JumpingEnemy(sf::Texture &image, float x, float y, float w, float h,
                    float speed, float range, float jumpForce = 0.35f);
        
        void update(float time) override;
    }; 
#endif
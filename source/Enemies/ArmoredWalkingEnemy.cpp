/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "ArmoredWalkingEnemy.h"

ArmoredWalkingEnemy::ArmoredWalkingEnemy(sf::Texture &image, float x, float y, float w, float h,
                                       float speed, float range)
    : WalkingEnemy(image, x, y, w, h, speed, range) {
    armor = 10;
    sprite.setTextureRect(sf::IntRect(0, 0, 34, 45));
}
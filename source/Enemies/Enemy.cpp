/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "Enemy.h"

Enemy::Enemy(sf::Texture &image, float x, float y, float w, float h,
             int armor, float speed, float range)
    : Entity(image, x, y, w, h),
      armor(armor),
      health(100),
      speed(speed),
      moveRange(range),
      startX(x),
      isAlive(true) {}

void Enemy::takeDamage(int damage) {
    int actualDamage = damage - armor;
    if (actualDamage < 0) actualDamage = 0;
    health -= actualDamage;
    std::cout << "Health: " << health << ", Armor: " << armor << std::endl;
    if (health <= 0) isAlive = false;
}
/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "Coin.h"

Coin::Coin(sf::Texture &image, float x, float y) 
    : Entity(image, x, y, 7, 8) {
    sprite.setTextureRect(sf::IntRect(4, 1348, 7, 8)); 
}

void Coin::update(float) {}

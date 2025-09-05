/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "WinBlock.h"

WinBlock::WinBlock(sf::Texture& image, float x, float y) 
    : Entity(image, x, y, 32, 32) {
    sprite.setTextureRect(sf::IntRect(112, 208, 32, 32));
}

void WinBlock::update(float) {}
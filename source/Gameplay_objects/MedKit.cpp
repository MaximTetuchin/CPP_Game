/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#include "MedKit.h"

MedKit::MedKit(sf::Texture& image, float x, float y) 
    : Entity(image, x, y, 7, 6) {
    sprite.setTextureRect(sf::IntRect(100, 693, 7, 6));
}

void MedKit::update(float) {}
/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#ifndef SPEED_BERRY_H
#define SPEED_BERRY_H
#include "../Entity.h"

class SpeedBerry : public Entity {
    public:
        SpeedBerry(sf::Texture& image, float x, float y);
        void update(float time) override;
    };
#endif
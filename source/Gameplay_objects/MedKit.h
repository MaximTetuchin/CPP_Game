/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
        CPP Game
*/
#ifndef MED_KIT_H
#define MED_KIT_H
#include "../Entity.h"

class MedKit : public Entity {
public:
    MedKit(sf::Texture& image, float x, float y);
    void update(float time) override;
};
#endif
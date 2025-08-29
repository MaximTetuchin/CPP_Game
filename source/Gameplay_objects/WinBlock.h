#ifndef WINBLOCK_H
#define WINBLOCK_H
#include "../Entity.h"
class WinBlock : public Entity {
public:
    WinBlock(sf::Texture& image, float x, float y);
    void update(float time) override;
};
#endif
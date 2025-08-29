#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>

class WinBlock : public Entity {
public:
    WinBlock(sf::Texture& image, float x, float y);
    void update(float time) override;
};
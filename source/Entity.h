#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity {
    public:
        sf::Sprite sprite;
        sf::FloatRect rect;
        float dx, dy;
        bool isAlive;
    
        Entity(sf::Texture &image, float x, float y, float w, float h);
        virtual ~Entity() = default;
    
        virtual void update(float time) = 0;
        virtual void draw(sf::RenderWindow &window);
    };


#endif
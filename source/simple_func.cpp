/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
CPP_Game
*/
#include "simple_func.h"

CircleShape createCircle(float radius, Vector2f position, Color fillColor) {
    CircleShape shape(radius);
    shape.setPosition(position);
    shape.setFillColor(fillColor);
    return shape;
}

void handleEvents(RenderWindow& window) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
    }
}

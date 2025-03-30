/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
CPP_Game
*/
#ifndef SIMPLE_FUNCTION
#define SIMPLE_FUNCTION

#include <SFML/Graphics.hpp>
using namespace sf;

CircleShape createCircle(float radius, Vector2f position, Color fillColor);
void handleEvents(RenderWindow& window);

#endif
/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
CPP_Game
*/
#include "simple_func.h"

int main() {
    RenderWindow window(VideoMode(800, 800), L"Placeholder");
    window.setVerticalSyncEnabled(true);
    
    CircleShape shape = createCircle(100.f, {100, 100}, Color::Green);

    while (window.isOpen()) {
        handleEvents(window);

        window.clear(Color::Blue);
        window.draw(shape);
        window.display();
    }
    return 0;
}

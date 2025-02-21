#include "simple_func.h"

int main() {
    RenderWindow window(VideoMode(400, 400), L"Новый проект");
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

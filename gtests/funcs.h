#ifndef FUNCS_H
#define FUNCS_H

#include <string>

class MockTexture {
public:
    bool loadFromFile(const std::string&) { return true; }
};

class MockSprite {};
class MockText {};
class MockFont {};

class MockRenderWindow {
public:
    void draw(const MockSprite&) {}
    void draw(const MockText&) {}
};

class MockIntRect {
public:
    MockIntRect() : left(0), top(0), width(0), height(0) {}
    MockIntRect(int l, int t, int w, int h) 
        : left(l), top(t), width(w), height(h) {}

    int left, top, width, height;

    bool intersects(const MockIntRect& other) const {
        return !(left > other.left + other.width || 
                 left + width < other.left ||
                 top > other.top + other.height ||
                 top + height < other.top);
    }
};

#endif // FUNCS_H

/* Maxim Tetuchin tetuhin@inbox.ru | st128993@student.spbu.ru
CPP_Game
*/
#include <gtest/gtest.h>
#include "../source/simple_func.h"

TEST(SFMLTest, CreateCircle) {
    CircleShape shape = createCircle(50.f, {10, 20}, Color::Red);
    EXPECT_FLOAT_EQ(shape.getRadius(), 50.f);
    EXPECT_EQ(shape.getPosition(), Vector2f(10, 20));
    EXPECT_EQ(shape.getFillColor(), Color::Red);
}

TEST(SFMLTest, ChangeColor) {
    CircleShape shape = createCircle(30.f, {0, 0}, Color::Blue);
    shape.setFillColor(Color::Yellow);
    EXPECT_EQ(shape.getFillColor(), Color::Yellow);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

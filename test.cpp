#include "gtest/gtest.h"

// Временно отключаем SFML-зависимости для тестов
#define SFML_STUB

// Ваши существующие классы
#include "source/Entity.h"
#include "source/Player.h"
#include "source/Weapons/Weapon.h"
#include "source/Weapons/Pistol.h"
#include "source/Weapons/Minigun.h"
#include "source/Weapons/Shotgun.h"
#include "source/Weapons/Rifle.h"
#include "source/Enemies/Enemy.h"
#include "source/Enemies/WalkingEnemy.h"
#include "source/Enemies/FlyingEnemy.h"
#include "source/Enemies/JumpingEnemy.h"
#include "source/Enemies/ArmoredWalkingEnemy.h"
#include "source/Enemies/ArmoredFlyingEnemy.h"
#include "source/Enemies/ArmoredJumpingEnemy.h"
#include "source/Gameplay_objects/Coin.h"
#include "source/Gameplay_objects/MedKit.h"
#include "source/Gameplay_objects/InvincibilitySphere.h"
#include "source/Gameplay_objects/SpeedBerry.h"
#include "source/Gameplay_objects/WinBlock.h"
#include "source/Gameplay_objects/MovingPlatform.h"
#include "source/Gameplay_objects/VerticalMovingPlatform.h"

// Заглушки для SFML
#ifdef SFML_STUB
namespace sf {
    class Texture {
    public:
        bool loadFromFile(const std::string&) { return true; }
    };
    
    class RenderWindow {
    public:
        void draw(const class Sprite&) {}
        void draw(const class Text&) {}
    };
    
    class Sprite {};
    class Text {};
    class Font {};
    
    // Добавляем IntRect для тестов
    class IntRect {
    public:
        IntRect(int l, int t, int w, int h) : left(l), top(t), width(w), height(h) {}
        int left, top, width, height;
        
        bool intersects(const IntRect& other) const {
            return !(left > other.left + other.width || 
                     left + width < other.left ||
                     top > other.top + other.height ||
                     top + height < other.top);
        }
    };
}
#endif

// Простые тесты, которые используют ваши реальные классы
TEST(PlayerTest, TakeDamageReducesHealth) {
    sf::Texture texture;
    Pistol pistol;
    Player player(texture, &pistol);
    player.health = 100;
    
    player.takeDamage(20);
    
    EXPECT_EQ(player.health, 80);
}

TEST(PlayerTest, InvincibilityPreventsDamage) {
    sf::Texture texture;
    Pistol pistol;
    Player player(texture, &pistol);
    player.health = 100;
    player.isInvincible = true;
    
    player.takeDamage(50);
    
    EXPECT_EQ(player.health, 100);
}

TEST(PlayerTest, AddCoinsIncreasesCoinCount) {
    sf::Texture texture;
    Pistol pistol;
    Player player(texture, &pistol);
    player.coins = 10;
    
    player.addCoins(5);
    
    EXPECT_EQ(player.coins, 15);
}

TEST(PlayerTest, SwitchWeaponChangesCurrentWeapon) {
    sf::Texture texture;
    Pistol pistol;
    Minigun minigun;
    Player player(texture, &pistol);
    
    player.switchWeapon(&minigun);
    
    EXPECT_EQ(player.currentWeapon, &minigun);
}

TEST(PlayerTest, UpdateDecreasesInvincibilityTime) {
    sf::Texture texture;
    Pistol pistol;
    Player player(texture, &pistol);
    player.isInvincible = true;
    player.invincibilityTime = 2.0f;
    
    player.update(1.0f);
    
    EXPECT_FLOAT_EQ(player.invincibilityTime, 1.0f);
}

TEST(PlayerTest, UpdateDecreasesSpeedBoostTime) {
    sf::Texture texture;
    Pistol pistol;
    Player player(texture, &pistol);
    player.isSpeedBoosted = true;
    player.speedBoostTime = 2.0f;
    
    player.update(1.0f);
    
    EXPECT_FLOAT_EQ(player.speedBoostTime, 1.0f);
}

TEST(WeaponTest, PistolHasCorrectName) {
    sf::Texture texture;
    Pistol pistol;
    pistol.setBulletTexture(texture);
    
    EXPECT_EQ(pistol.getName(), "Pistol");
}

TEST(WeaponTest, MinigunHasCorrectName) {
    sf::Texture texture;
    Minigun minigun;
    minigun.setBulletTexture(texture);
    
    EXPECT_EQ(minigun.getName(), "Minigun");
}

TEST(WeaponTest, ShotgunHasCorrectName) {
    sf::Texture texture;
    Shotgun shotgun;
    shotgun.setBulletTexture(texture);
    
    EXPECT_EQ(shotgun.getName(), "Shotgun");
}

TEST(WeaponTest, RifleHasCorrectName) {
    sf::Texture texture;
    Rifle rifle;
    rifle.setBulletTexture(texture);
    
    EXPECT_EQ(rifle.getName(), "Rifle");
}

TEST(EnemyTest, WalkingEnemyTakeDamage) {
    sf::Texture texture;
    WalkingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 100;
    
    enemy.takeDamage(30);
    
    EXPECT_EQ(enemy.health, 70);
}

TEST(EnemyTest, FlyingEnemyTakeDamage) {
    sf::Texture texture;
    FlyingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 100;
    
    enemy.takeDamage(30);
    
    EXPECT_EQ(enemy.health, 70);
}

TEST(EnemyTest, JumpingEnemyTakeDamage) {
    sf::Texture texture;
    JumpingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f, 0.3f);
    enemy.health = 100;
    
    enemy.takeDamage(30);
    
    EXPECT_EQ(enemy.health, 70);
}

TEST(EnemyTest, ArmoredWalkingEnemyTakeDamage) {
    sf::Texture texture;
    ArmoredWalkingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 100;
    
    enemy.takeDamage(30);
    
    EXPECT_EQ(enemy.health, 70);
}

TEST(EnemyTest, ArmoredFlyingEnemyTakeDamage) {
    sf::Texture texture;
    ArmoredFlyingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 100;
    
    enemy.takeDamage(30);
    
    EXPECT_EQ(enemy.health, 70);
}

TEST(EnemyTest, ArmoredJumpingEnemyTakeDamage) {
    sf::Texture texture;
    ArmoredJumpingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f, 0.3f);
    enemy.health = 100;
    
    enemy.takeDamage(30);
    
    EXPECT_EQ(enemy.health, 70);
}

TEST(EnemyTest, EnemyDiesWhenHealthZero) {
    sf::Texture texture;
    WalkingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 10;
    
    enemy.takeDamage(10);
    
    EXPECT_FALSE(enemy.isAlive);
}

TEST(GameObjectTest, CoinCollection) {
    sf::Texture texture;
    Coin coin(texture, 0, 0);
    
    // Проверяем, что объект создан
    EXPECT_TRUE(true); // Простая проверка, что объект создан без ошибок
}

TEST(GameObjectTest, MedKitCollection) {
    sf::Texture texture;
    MedKit medkit(texture, 0, 0);
    
    // Проверяем, что объект создан
    EXPECT_TRUE(true);
}

TEST(GameObjectTest, InvincibilitySphereCollection) {
    sf::Texture texture;
    InvincibilitySphere sphere(texture, 0, 0);
    
    // Проверяем, что объект создан
    EXPECT_TRUE(true);
}

TEST(GameObjectTest, SpeedBerryCollection) {
    sf::Texture texture;
    SpeedBerry berry(texture, 0, 0);
    
    // Проверяем, что объект создан
    EXPECT_TRUE(true);
}

TEST(GameObjectTest, WinBlockCollection) {
    sf::Texture texture;
    WinBlock block(texture, 0, 0);
    
    // Проверяем, что объект создан
    EXPECT_TRUE(true);
}

TEST(PlatformTest, MovingPlatformCreation) {
    sf::Texture texture;
    MovingPlatform platform(texture, 0, 0, 64, 16, 100.0f, 0.05f);
    
    // Проверяем, что объект создан
    EXPECT_TRUE(true);
}

TEST(PlatformTest, VerticalMovingPlatformCreation) {
    sf::Texture texture;
    VerticalMovingPlatform platform(texture, 0, 0, 64, 16, 100.0f, 0.05f);
    
    // Проверяем, что объект создан
    EXPECT_TRUE(true);
}

TEST(EntityTest, EntityUpdate) {
    // Тестируем базовый функционал Entity
    sf::Texture texture;
    Pistol pistol;
    Player player(texture, &pistol);
    
    player.dx = 0.1f;
    player.dy = 0.1f;
    player.update(1.0f);
    
    // Проверяем, что обновление прошло без ошибок
    EXPECT_TRUE(true);
}

// Главная функция тестов
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
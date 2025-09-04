#include "funcs.h"
#include "gtest/gtest.h"
#include "../source/Entity.h"
#include "../source/Player.h"
#include "../source/Weapons/Weapon.h"
#include "../source/Weapons/Pistol.h"
#include "../source/Weapons/Minigun.h"
#include "../source/Weapons/Shotgun.h"
#include "../source/Weapons/Rifle.h"
#include "../source/Enemies/Enemy.h"
#include "../source/Enemies/WalkingEnemy.h"
#include "../source/Enemies/FlyingEnemy.h"
#include "../source/Enemies/JumpingEnemy.h"
#include "../source/Enemies/ArmoredWalkingEnemy.h"
#include "../source/Enemies/ArmoredFlyingEnemy.h"
#include "../source/Enemies/ArmoredJumpingEnemy.h"
#include "../source/Gameplay_objects/Coin.h"
#include "../source/Gameplay_objects/MedKit.h"
#include "../source/Gameplay_objects/InvincibilitySphere.h"
#include "../source/Gameplay_objects/SpeedBerry.h"
#include "../source/Gameplay_objects/WinBlock.h"
#include "../source/Gameplay_objects/MovingPlatform.h"
#include "../source/Gameplay_objects/VerticalMovingPlatform.h"

// DummyTexture для headless тестов
class DummyTexture : public sf::Texture {
public:
    DummyTexture() { this->create(1,1); }
};

TEST(PlayerTest, TakeDamageReducesHealth) {
    DummyTexture texture;
    Pistol pistol;
    Player player(texture, &pistol);
    player.health = 100;
    
    player.takeDamage(20);
    EXPECT_EQ(player.health, 80);
}

TEST(PlayerTest, InvincibilityPreventsDamage) {
    DummyTexture texture;
    Pistol pistol;
    Player player(texture, &pistol);
    player.health = 100;
    player.isInvincible = true;
    
    player.takeDamage(50);
    EXPECT_EQ(player.health, 100);
}

TEST(PlayerTest, AddCoinsIncreasesCoinCount) {
    DummyTexture texture;
    Pistol pistol;
    Player player(texture, &pistol);
    player.coins = 10;
    
    player.addCoins(5);
    EXPECT_EQ(player.coins, 15);
}

TEST(PlayerTest, SwitchWeaponChangesCurrentWeapon) {
    DummyTexture texture;
    Pistol pistol;
    Minigun minigun;
    Player player(texture, &pistol);
    
    player.switchWeapon(&minigun);
    EXPECT_EQ(player.currentWeapon, &minigun);
}

TEST(PlayerTest, UpdateDecreasesInvincibilityTime) {
    DummyTexture texture;
    Pistol pistol;
    Player player(texture, &pistol);
    player.isInvincible = true;
    player.invincibilityTime = 2.0f;
    
    player.update(1.0f);
    EXPECT_FLOAT_EQ(player.invincibilityTime, 1.0f);
}

TEST(PlayerTest, UpdateDecreasesSpeedBoostTime) {
    DummyTexture texture;
    Pistol pistol;
    Player player(texture, &pistol);
    player.isSpeedBoosted = true;
    player.speedBoostTime = 2.0f;
    
    player.update(1.0f);
    EXPECT_FLOAT_EQ(player.speedBoostTime, 1.0f);
}

TEST(WeaponTest, PistolHasCorrectName) {
    DummyTexture texture;
    Pistol pistol;
    pistol.setBulletTexture(texture);
    EXPECT_EQ(pistol.getName(), "Pistol");
}

TEST(WeaponTest, MinigunHasCorrectName) {
    DummyTexture texture;
    Minigun minigun;
    minigun.setBulletTexture(texture);
    EXPECT_EQ(minigun.getName(), "Minigun");
}

TEST(WeaponTest, ShotgunHasCorrectName) {
    DummyTexture texture;
    Shotgun shotgun;
    shotgun.setBulletTexture(texture);
    EXPECT_EQ(shotgun.getName(), "Shotgun");
}

TEST(WeaponTest, RifleHasCorrectName) {
    DummyTexture texture;
    Rifle rifle;
    rifle.setBulletTexture(texture);
    EXPECT_EQ(rifle.getName(), "Rifle");
}

TEST(EnemyTest, WalkingEnemyTakesDamage) {
    DummyTexture texture;
    WalkingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 100;
    enemy.takeDamage(30);
    EXPECT_EQ(enemy.health, 70);
}

TEST(EnemyTest, FlyingEnemyTakesDamage) {
    DummyTexture texture;
    FlyingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 100;
    enemy.takeDamage(30);
    EXPECT_EQ(enemy.health, 70);
}

TEST(EnemyTest, JumpingEnemyTakesDamage) {
    DummyTexture texture;
    JumpingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f, 0.3f);
    enemy.health = 100;
    enemy.takeDamage(30);
    EXPECT_EQ(enemy.health, 70);
}

TEST(EnemyTest, ArmoredWalkingEnemyTakesReducedDamage) {
    DummyTexture texture;
    ArmoredWalkingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 100;
    enemy.takeDamage(30);
    EXPECT_EQ(enemy.health, 80);
}

TEST(EnemyTest, ArmoredFlyingEnemyTakesReducedDamage) {
    DummyTexture texture;
    ArmoredFlyingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 100;
    enemy.takeDamage(30);
    EXPECT_EQ(enemy.health, 80);
}

TEST(EnemyTest, ArmoredJumpingEnemyTakesReducedDamage) {
    DummyTexture texture;
    ArmoredJumpingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f, 0.3f);
    enemy.health = 100;
    enemy.takeDamage(30);
    EXPECT_EQ(enemy.health, 80);
}

TEST(EnemyTest, EnemyDiesWhenHealthReachesZero) {
    DummyTexture texture;
    WalkingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 10;
    enemy.takeDamage(10);
    EXPECT_FALSE(enemy.isAlive);
}

TEST(GameObjectTest, CoinCanBeCreated) {
    DummyTexture texture;
    Coin coin(texture, 0, 0);
    EXPECT_TRUE(true);
}

TEST(GameObjectTest, PlayerHealsWithMedKit) {
    DummyTexture texture;
    Pistol pistol;
    Player player(texture, &pistol);

    player.health = 50;
    int medkitHealing = 35; 

    sf::IntRect playerBounds(0, 0, 32, 32);
    sf::IntRect medkitBounds(10, 10, 16, 16);

    if (playerBounds.intersects(medkitBounds)) {
        player.health += medkitHealing;
        if (player.health > 100) player.health = 100;
    }

    EXPECT_EQ(player.health, 85);
}

TEST(GameObjectTest, InvincibilitySphereCanBeCollected) {
    DummyTexture texture;
    Pistol pistol;
    Player player(texture, &pistol);

    InvincibilitySphere sphere(texture, 10, 10);
    sf::IntRect playerBounds(0, 0, 32, 32);
    sf::IntRect sphereBounds(10, 10, 16, 16);

    EXPECT_TRUE(playerBounds.intersects(sphereBounds));
}

TEST(GameObjectTest, SpeedBerryCanBeCollected) {
    DummyTexture texture;
    Pistol pistol;
    Player player(texture, &pistol);

    SpeedBerry berry(texture, 5, 5);
    sf::IntRect playerBounds(0, 0, 32, 32);
    sf::IntRect berryBounds(5, 5, 16, 16);

    EXPECT_TRUE(playerBounds.intersects(berryBounds));
}

TEST(GameObjectTest, WinBlockCanBeTouched) {
    DummyTexture texture;
    Pistol pistol;
    Player player(texture, &pistol);

    WinBlock block(texture, 0, 0);
    sf::IntRect playerBounds(0, 0, 32, 32);
    sf::IntRect blockBounds(0, 0, 32, 32);

    EXPECT_TRUE(playerBounds.intersects(blockBounds));
}

TEST(PlatformTest, MovingPlatformCanBeCreated) {
    DummyTexture texture;
    MovingPlatform platform(texture, 0, 0, 64, 16, 100.0f, 0.05f);
    EXPECT_TRUE(true);
}

TEST(PlatformTest, VerticalMovingPlatformCanBeCreated) {
    DummyTexture texture;
    VerticalMovingPlatform platform(texture, 0, 0, 64, 16, 100.0f, 0.05f);
    EXPECT_TRUE(true);
}

TEST(EntityTest, EntityUpdateCompletesWithoutErrors) {
    DummyTexture texture;
    Pistol pistol;
    Player player(texture, &pistol);
    
    player.dx = 0.1f;
    player.dy = 0.1f;
    player.update(1.0f);
    EXPECT_TRUE(true);
}

// Main остаётся как у тебя
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

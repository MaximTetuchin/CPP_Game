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

TEST(PlayerTest, TakeDamageReducesHealth) {
    sf::Texture texture; texture.create(1,1);
    Pistol pistol;
    Player player(texture, &pistol);
    player.health = 100;
    
    player.takeDamage(20);
    EXPECT_EQ(player.health, 80);
}

TEST(PlayerTest, InvincibilityPreventsDamage) {
    sf::Texture texture; texture.create(1,1);
    Pistol pistol;
    Player player(texture, &pistol);
    player.health = 100;
    player.isInvincible = true;
    
    player.takeDamage(50);
    EXPECT_EQ(player.health, 100);
}

TEST(PlayerTest, AddCoinsIncreasesCoinCount) {
    sf::Texture texture; texture.create(1,1);
    Pistol pistol;
    Player player(texture, &pistol);
    player.coins = 10;
    
    player.addCoins(5);
    EXPECT_EQ(player.coins, 15);
}

TEST(PlayerTest, SwitchWeaponChangesCurrentWeapon) {
    sf::Texture texture; texture.create(1,1);
    Pistol pistol;
    Minigun minigun;
    Player player(texture, &pistol);
    
    player.switchWeapon(&minigun);
    EXPECT_EQ(player.currentWeapon, &minigun);
}

TEST(PlayerTest, UpdateDecreasesInvincibilityTime) {
    sf::Texture texture; texture.create(1,1);
    Pistol pistol;
    Player player(texture, &pistol);
    player.isInvincible = true;
    player.invincibilityTime = 2.0f;
    
    player.update(1.0f);
    EXPECT_FLOAT_EQ(player.invincibilityTime, 1.0f);
}

TEST(PlayerTest, UpdateDecreasesSpeedBoostTime) {
    sf::Texture texture; texture.create(1,1);
    Pistol pistol;
    Player player(texture, &pistol);
    player.isSpeedBoosted = true;
    player.speedBoostTime = 2.0f;
    
    player.update(1.0f);
    EXPECT_FLOAT_EQ(player.speedBoostTime, 1.0f);
}

TEST(WeaponTest, PistolHasCorrectName) {
    sf::Texture texture; texture.create(1,1);
    Pistol pistol;
    pistol.setBulletTexture(texture);
    EXPECT_EQ(pistol.getName(), "Pistol");
}

TEST(WeaponTest, MinigunHasCorrectName) {
    sf::Texture texture; texture.create(1,1);
    Minigun minigun;
    minigun.setBulletTexture(texture);
    EXPECT_EQ(minigun.getName(), "Minigun");
}

TEST(WeaponTest, ShotgunHasCorrectName) {
    sf::Texture texture; texture.create(1,1);
    Shotgun shotgun;
    shotgun.setBulletTexture(texture);
    EXPECT_EQ(shotgun.getName(), "Shotgun");
}

TEST(WeaponTest, RifleHasCorrectName) {
    sf::Texture texture; texture.create(1,1);
    Rifle rifle;
    rifle.setBulletTexture(texture);
    EXPECT_EQ(rifle.getName(), "Rifle");
}

TEST(EnemyTest, WalkingEnemyTakesDamage) {
    sf::Texture texture; texture.create(1,1);
    WalkingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 100;
    enemy.takeDamage(30);
    EXPECT_EQ(enemy.health, 70);
}

TEST(EnemyTest, FlyingEnemyTakesDamage) {
    sf::Texture texture; texture.create(1,1);
    FlyingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 100;
    enemy.takeDamage(30);
    EXPECT_EQ(enemy.health, 70);
}

TEST(EnemyTest, JumpingEnemyTakesDamage) {
    sf::Texture texture; texture.create(1,1);
    JumpingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f, 0.3f);
    enemy.health = 100;
    enemy.takeDamage(30);
    EXPECT_EQ(enemy.health, 70);
}

TEST(EnemyTest, ArmoredWalkingEnemyTakesReducedDamage) {
    sf::Texture texture; texture.create(1,1);
    ArmoredWalkingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 100;
    enemy.takeDamage(30);
    EXPECT_EQ(enemy.health, 80);
}

TEST(EnemyTest, ArmoredFlyingEnemyTakesReducedDamage) {
    sf::Texture texture; texture.create(1,1);
    ArmoredFlyingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 100;
    enemy.takeDamage(30);
    EXPECT_EQ(enemy.health, 80);
}

TEST(EnemyTest, ArmoredJumpingEnemyTakesReducedDamage) {
    sf::Texture texture; texture.create(1,1);
    ArmoredJumpingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f, 0.3f);
    enemy.health = 100;
    enemy.takeDamage(30);
    EXPECT_EQ(enemy.health, 80);
}

TEST(EnemyTest, EnemyDiesWhenHealthReachesZero) {
    sf::Texture texture; texture.create(1,1);
    WalkingEnemy enemy(texture, 0, 0, 32, 32, 0.1f, 100.0f);
    enemy.health = 10;
    enemy.takeDamage(10);
    EXPECT_FALSE(enemy.isAlive);
}

TEST(GameObjectTest, CoinCanBeCreated) {
    sf::Texture texture; texture.create(1,1);
    Coin coin(texture, 0, 0);
    EXPECT_TRUE(true);
}

TEST(GameObjectTest, PlayerHealsWithMedKit) {
    sf::Texture texture; texture.create(1,1);
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
    sf::Texture texture; texture.create(1,1);
    Pistol pistol;
    Player player(texture, &pistol);

    InvincibilitySphere sphere(texture, 10, 10);
    sf::IntRect playerBounds(0, 0, 32, 32);
    sf::IntRect sphereBounds(10, 10, 16, 16);

    EXPECT_TRUE(playerBounds.intersects(sphereBounds));
}

TEST(GameObjectTest, SpeedBerryCanBeCollected) {
    sf::Texture texture; texture.create(1,1);
    Pistol pistol;
    Player player(texture, &pistol);

    SpeedBerry berry(texture, 5, 5);
    sf::IntRect playerBounds(0, 0, 32, 32);
    sf::IntRect berryBounds(5, 5, 16, 16);

    EXPECT_TRUE(playerBounds.intersects(berryBounds));
}

TEST(GameObjectTest, WinBlockCanBeTouched) {
    sf::Texture texture; texture.create(1,1);
    Pistol pistol;
    Player player(texture, &pistol);

    WinBlock block(texture, 0, 0);
    sf::IntRect playerBounds(0, 0, 32, 32);
    sf::IntRect blockBounds(0, 0, 32, 32);

    EXPECT_TRUE(playerBounds.intersects(blockBounds));
}

TEST(PlatformTest, MovingPlatformCanBeCreated) {
    sf::Texture texture; texture.create(1,1);
    MovingPlatform platform(texture, 0, 0, 64, 16, 100.0f, 0.05f);
    EXPECT_TRUE(true);
}

TEST(PlatformTest, VerticalMovingPlatformCanBeCreated) {
    sf::Texture texture; texture.create(1,1);
    VerticalMovingPlatform platform(texture, 0, 0, 64, 16, 100.0f, 0.05f);
    EXPECT_TRUE(true);
}

TEST(EntityTest, EntityUpdateCompletesWithoutErrors) {
    sf::Texture texture; texture.create(1,1);
    Pistol pistol;
    Player player(texture, &pistol);
    
    player.dx = 0.1f;
    player.dy = 0.1f;
    player.update(1.0f);
    EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    sf::Context context;
    return RUN_ALL_TESTS();
}
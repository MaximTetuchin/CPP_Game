#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Weapons/Weapon.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Player : public Entity {
public:
    int coins;
    bool onGround;
    float currentFrame;
    float idleFrame;
    bool lastAction;
    Weapon* currentWeapon;
    
    int health;
    int maxHealth;
    float invincibilityTime;
    float speedMultiplier;
    float speedBoostTime;
    bool isSpeedBoosted;
    bool isInvincible;

    float respawnX; // Добавлено: X координата респавна
    float respawnY; // Добавлено: Y координата респавна

    Player(sf::Texture& image, Weapon* startingWeapon);
    
    void addCoins(int amount);
    void takeDamage(int damage);
    void switchWeapon(Weapon* newWeapon);
    void update(float time) override;
    void Collision(int dir);
    void respawn(); // Добавлено: метод респавна
};
#endif
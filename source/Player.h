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

    float respawnX;
    float respawnY;

    Player(sf::Texture& image, Weapon* startingWeapon);
    
    void addCoins(int amount);
    void takeDamage(int damage);
    void switchWeapon(Weapon* newWeapon);
    void update(float time) override;
    void Collision(int dir);
    void respawn();
    void setRespawnPoint(float x, float y); 
    void setPosition(float x, float y); 
};

#endif
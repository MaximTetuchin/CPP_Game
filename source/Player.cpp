#include "Player.h"
#include "Gameplay_objects/Tilemap.h"
#include "Constants.h" // Предполагаем, что у вас есть файл с константами

Player::Player(sf::Texture& image, Weapon* startingWeapon)
    : Entity(image, 7*32, 9*32, 40, 50),
      coins(0),
      onGround(false),
      currentFrame(0),
      lastAction(true),
      currentWeapon(startingWeapon),
      health(100), 
      maxHealth(100),
      invincibilityTime(0),
      speedMultiplier(1.0f),
      speedBoostTime(0),
      isSpeedBoosted(false),
      isInvincible(false),
      respawnX(7*32),
      respawnY(9*32) {
    
    // Убедимся, что спрайт находится в правильной позиции
    sprite.setPosition(rect.left, rect.top);
}

void Player::addCoins(int amount) {
    coins += amount;
}

void Player::takeDamage(int damage) {
    if(!isInvincible) {
        health -= damage;
        std::cout << "damage was taken!!!!!!!!!!!!!!!\n";
        if(health < 0) health = 0;
        if (health == 0) {
            respawn(); // Респавн при достижении 0 HP
        }
        invincibilityTime = 1500.0f;
        isInvincible = true;
    }
}

void Player::switchWeapon(Weapon* newWeapon) {
    currentWeapon = newWeapon;
}

void Player::update(float time) {
    if(isSpeedBoosted) {
        speedBoostTime -= time;
        if(speedBoostTime <= 0) {
            speedMultiplier = 1.0f;
            isSpeedBoosted = false;
        }
    }
    if(isInvincible) {
        invincibilityTime -= time;
        if(invincibilityTime <= 0) {
            isInvincible = false;
        }
    }
    
    rect.left += dx * time;
    Collision(0);

    if (!onGround) dy += 0.0005 * time;
    rect.top += dy * time;
    onGround = false;
    Collision(1);

    currentFrame += 0.005 * time;
    idleFrame = currentFrame / 1.5;

    if (currentFrame > 6) currentFrame -= 6;
    if (idleFrame > 3) idleFrame -= 3;

    if (dx > 0) {
        sprite.setTextureRect(sf::IntRect(40 * int(currentFrame), 244, 40, 50));
        lastAction = true;
    } 
    else if (dx < 0) {
        sprite.setTextureRect(sf::IntRect(40 * int(currentFrame) + 40, 244, -40, 50));
        lastAction = false;
    } 
    else {
        if (lastAction) {
            sprite.setTextureRect(sf::IntRect(43 * int(idleFrame) + 4, 188, 40, 50));
        } else {
            sprite.setTextureRect(sf::IntRect(43 * int(idleFrame) + 4 + 40, 188, -40, 50));
        }
    }

    // Обновляем позицию спрайта
    sprite.setPosition(rect.left, rect.top);

    if (currentWeapon) {
        currentWeapon->update(time);
    }
    dx = 0;
}

void Player::Collision(int dir) {
    for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
        // Добавляем проверку границ массива
        if (i < 0 || i >= H) continue;
        
        for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
            // Добавляем проверку границ массива
            if (j < 0 || j >= W) continue;
            
            if (TileMap[i][j] == 'B' || TileMap[i][j] == 'G' || TileMap[i][j] == 'W' || TileMap[i][j] == 'Z') {
                if (TileMap[i][j] == 'Z') {
                    health = 100;
                    respawn();
                }
                if ((dx > 0) && (dir == 0)) rect.left = j * 32 - rect.width;
                if ((dx < 0) && (dir == 0)) rect.left = j * 32 + 32;
                if ((dy > 0) && (dir == 1)) { 
                    rect.top = i * 32 - rect.height; 
                    dy = 0; 
                    onGround = true; 
                }
                if ((dy < 0) && (dir == 1)) { 
                    rect.top = i * 32 + 32; 
                    dy = 0; 
                }
            }
            if (TileMap[i][j] == '0') TileMap[i][j] = ' ';
        }
    }
}

void Player::respawn() {
    health = maxHealth;
    rect.left = respawnX;
    rect.top = respawnY;
    sprite.setPosition(respawnX, respawnY);
    dx = 0;
    dy = 0;
    speedMultiplier = 1.0f;
    speedBoostTime = 0;
    isSpeedBoosted = false;
    isInvincible = true;
    invincibilityTime = 1500.0f;
}

void Player::setRespawnPoint(float x, float y) {
    respawnX = x;
    respawnY = y;
}

void Player::setPosition(float x, float y) {
    rect.left = x;
    rect.top = y;
    sprite.setPosition(x, y);
    
    dx = 0;
    dy = 0;
    onGround = false;
    
    Collision(0);
    Collision(1); 
    
    sprite.setPosition(rect.left, rect.top);
}
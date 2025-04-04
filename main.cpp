#include "source/Constants.h"

#include "source/Gameplay_objects/Tilemap.h"
#include "source/Entity.h"
#include "source/Gameplay_objects/Coin.h"
#include "source/Gameplay_objects/MovingPlatform.h"
#include "source/Gameplay_objects/VerticalMovingPlatform.h"
#include "source/Weapons/Bullet.h"
#include "source/Weapons/Pistol.h"
#include "source/Weapons/Weapon.h"
#include "source/Weapons/Minigun.h"
#include "source/Weapons/Shotgun.h"
#include "source/Weapons/Rifle.h"
#include "source/Player.h"

#include "source/Enemies/Enemy.h"
#include "source/Enemies/WalkingEnemy.h"
#include "source/Enemies/JumpingEnemy.h"
#include "source/Enemies/FlyingEnemy.h"
#include "source/Enemies/ArmoredWalkingEnemy.h"
#include "source/Enemies/ArmoredJumpingEnemy.h"
#include "source/Enemies/ArmoredFlyingEnemy.h"

#include "source/Gameplay_objects/MedKit.h"
#include "source/Gameplay_objects/InvincibilitySphere.h"
#include "source/Gameplay_objects/SpeedBerry.h"


std::vector<Entity*> entities; 
sf::Texture basicAssets;  
sf::RectangleShape rectangle(sf::Vector2f(32, 32));


int main() {
    sf::Clock clock;
    sf::View uiView;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dakaraima!", sf::Style::Titlebar | sf::Style::Close);
    window.setSize(sf::Vector2u(800, 600));
    uiView.setSize(window.getSize().x, window.getSize().y); 
    uiView.setCenter(window.getSize().x / 2, window.getSize().y / 2);

    sf::View camera;
    camera.setSize(720, 540);
    camera.setCenter(400, 300);
    window.setView(camera);

    //loading fonts
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text coinText,weaponText,hpText;
    hpText.setFont(font); hpText.setCharacterSize(24);
    hpText.setFillColor(sf::Color::Black); hpText.setPosition(10, 80);

    coinText.setFont(font); coinText.setCharacterSize(24);
    coinText.setFillColor(sf::Color::Black); coinText.setPosition(10, 45);

    weaponText.setFont(font); weaponText.setCharacterSize(24); 
    weaponText.setFillColor(sf::Color::Black); weaponText.setPosition(10, 10);

    // Loading basic assets
    sf::Texture playerTex, bulletTex,basicAssets;
    sf::IntRect tileTex(80, 208, 32, 32);
    basicAssets.loadFromFile("assets/World-Tiles.png");
    playerTex.loadFromFile("assets/fang.png");
    bulletTex.loadFromFile("assets/fang.png");
    // Walking enemy init
    sf::Texture WalkingEnemyTex,ArmoredWalkingEnemyTex;
    WalkingEnemyTex.loadFromFile("assets/edited_assets/walkingEnemy.png");
    ArmoredWalkingEnemyTex.loadFromFile("assets/edited_assets/armoredWalkingEnemy.png");
    // Flying enemy init
    sf::Texture FlyingEnemyTex,ArmoredFlyingEnemyTex;
    FlyingEnemyTex.loadFromFile("assets/edited_assets/flyingEnemy.png");
    ArmoredFlyingEnemyTex.loadFromFile("assets/edited_assets/armoredFlyingEnemy.png");
    // Jumping enemy init
    sf::Texture JumpingEnemyTex,ArmoredJumpingTex;
    JumpingEnemyTex.loadFromFile("assets/edited_assets/jumpingEnemy.png");
    ArmoredJumpingTex.loadFromFile("assets/edited_assets/armoredJumpingEnemy.png");
    // Weapons init
    Pistol pistol;Minigun minigun;Shotgun shotgun;Rifle rifle;
    pistol.setBulletTexture(bulletTex); minigun.setBulletTexture(bulletTex);
    shotgun.setBulletTexture(bulletTex); rifle.setBulletTexture(bulletTex);

    // Basics init
    Player player(playerTex, &pistol);
    entities.push_back(&player);
    weaponText.setString("Weapon: " + player.currentWeapon->getName());

    // Creating entities before starting the game
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            //^ Defaulf enemies 
            if (TileMap[i][j] == 'E') {
                entities.push_back(new WalkingEnemy(WalkingEnemyTex, j*32, i*32, 34, 45, 0.05f, 100.0f));
                TileMap[i][j] = ' ';
            }
            if (TileMap[i][j] == 'F') {
                entities.push_back(new FlyingEnemy(FlyingEnemyTex, j * 32, i * 32, 42, 42, 0.05f, 100.0f));
                TileMap[i][j] = ' ';
            }
            if (TileMap[i][j] == 'J') {
                entities.push_back(new JumpingEnemy(JumpingEnemyTex, j*32, i*32, 39, 45, 0.05f, 100.0f, 0.3f));
                TileMap[i][j] = ' ';
            }     
            //^ Armored enemies 
            if (TileMap[i][j] == 'D') {
                entities.push_back(new ArmoredWalkingEnemy(ArmoredWalkingEnemyTex, j*32, i*32, 34, 45, 0.05f, 100.0f));
                TileMap[i][j] = ' ';
            }
            if (TileMap[i][j] == 'V') {
                entities.push_back(new ArmoredFlyingEnemy(ArmoredFlyingEnemyTex, j*32, i*32, 47, 45, 0.05f, 100.0f));
                TileMap[i][j] = ' ';
            }
            if (TileMap[i][j] == 'M') {
                entities.push_back(new ArmoredJumpingEnemy(ArmoredJumpingTex, j*32, i*32, 39, 45, 0.05f, 100.0f, 0.3f));
                TileMap[i][j] = ' ';
            }  
            //^ game entity 
            if (TileMap[i][j] == 'C') {
                entities.push_back(new Coin(basicAssets, j*32 + 8, i*32 + 8));
                TileMap[i][j] = ' ';
            }
            if (TileMap[i][j] == 'L') {
                entities.push_back(new MovingPlatform(basicAssets, j*32, i*32, 64, 16, 100.0f, 0.05f));
                TileMap[i][j] = ' ';
            }
            if (TileMap[i][j] == 'U') {
                entities.push_back(new VerticalMovingPlatform(basicAssets, j * 32, i * 32, 64, 16, 100.0f, 0.05f));
                TileMap[i][j] = ' ';
            }
            if (TileMap[i][j] == 'H') {
                entities.push_back(new MedKit(basicAssets, j*32+12, i*32+8));
                TileMap[i][j] = ' ';
            }
            if (TileMap[i][j] == 'I') {
                entities.push_back(new InvincibilitySphere(basicAssets, j*32+15, i*32+5));
                TileMap[i][j] = ' ';
            }
            if (TileMap[i][j] == 'S') {
                entities.push_back(new SpeedBerry(basicAssets, j*32, i*32));
                TileMap[i][j] = ' ';
            }
        }
    }

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / TIME_DIVISOR;
        if (time > MAX_TIME) time = MAX_TIME;
    
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    
        // Keyboard handle
        // Moving left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
            player.dx = -BASE_MOVE_SPEED * player.speedMultiplier;
            
        // Moving right
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
            player.dx = BASE_MOVE_SPEED * player.speedMultiplier;

        // Jumping   
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.onGround) {
            player.dy = JUMP_SPEED;
            player.onGround = false;
        }

        // Shooting
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (player.currentWeapon && player.currentWeapon->tryFire(entities, 
                    player.rect.left + (player.lastAction ? BULLET_X_OFFSET_ACTION : BULLET_X_OFFSET_DEFAULT),
                    player.rect.top + BULLET_Y_OFFSET,
                    player.lastAction)) { 
            }
        }
    
        // Weapons selection
        for (int i = sf::Keyboard::Num1; i <= sf::Keyboard::Num4; ++i) {
            if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i))) {
                Weapon* selectedWeapon = nullptr;
                switch (i) {
                    case sf::Keyboard::Num1: selectedWeapon = &pistol; break;
                    case sf::Keyboard::Num2: selectedWeapon = &minigun; break;
                    case sf::Keyboard::Num3: selectedWeapon = &shotgun; break;
                    case sf::Keyboard::Num4: selectedWeapon = &rifle; break;
                }
                if (selectedWeapon) {
                    player.switchWeapon(selectedWeapon);
                    weaponText.setString("Weapon: " + player.currentWeapon->getName());
                }
                break;
            }
        }
    
        // Entity update
        for (auto it = entities.begin(); it != entities.end();) {
            Entity* entity = *it;
            entity->update(time);
            
            // Bullets collision update
            if (auto* bullet = dynamic_cast<Bullet*>(entity)) {
                bool bulletHit = false;
                for (auto* enemy : entities) {
                    if (auto* enemyPtr = dynamic_cast<Enemy*>(enemy)) {
                        if (enemyPtr->isAlive && bullet->rect.intersects(enemyPtr->rect)) {
                            enemyPtr->takeDamage(bullet->damage);
                            bulletHit = true;
                            break;
                        }
                    }
                }
                if (bulletHit || !bullet->isAlive) {
                    delete bullet;
                    it = entities.erase(it);
                    continue;
                }
            }
            
            // Enemies collision update
            if (auto* enemy = dynamic_cast<Enemy*>(entity)) {
                if (!enemy->isAlive) {
                    delete enemy;
                    it = entities.erase(it);
                    continue;
                }
                if (enemy->isAlive && player.rect.intersects(enemy->rect)) {
                    player.takeDamage(DAMAGE_ON_ENEMY_COLLISION);
                }
            }
            
            // Coins collision update
            if (auto* coin = dynamic_cast<Coin*>(entity)) {
                if (player.rect.intersects(coin->rect)) {
                    player.addCoins(COIN_VALUE);
                    delete coin;
                    it = entities.erase(it);
                    continue;
                }
            }
            
            // Medkit update
            if (auto* medkit = dynamic_cast<MedKit*>(entity)) {
                if (player.rect.intersects(medkit->rect)) {
                    player.health = std::min(player.health + HEAL_AMOUNT, player.maxHealth);
                    delete medkit;
                    it = entities.erase(it);
                    continue;
                }
            }
    
            // InvincibilitySphere update
            if (auto* invincibilitySphere = dynamic_cast<InvincibilitySphere*>(entity)) {
                if (player.rect.intersects(invincibilitySphere->rect)) {
                    player.isInvincible = true;
                    player.invincibilityTime = INVINCIBILITY_DURATION;
                    delete invincibilitySphere;
                    it = entities.erase(it);
                    continue;
                }
            }
    
            // SpeedBerry update
            if (auto* speedBerry = dynamic_cast<SpeedBerry*>(entity)) {
                if (player.rect.intersects(speedBerry->rect)) {
                    player.speedMultiplier = SPEED_BOOST_MULTIPLIER;
                    player.speedBoostTime = SPEED_BOOST_DURATION;
                    player.isSpeedBoosted = true;
                    delete speedBerry;
                    it = entities.erase(it);
                    continue;
                }
            }
            
            // Platforms update
            if (auto* platform = dynamic_cast<MovingPlatform*>(entity)) {
                if (player.rect.intersects(platform->rect)) {
                    float playerBottom = player.rect.top + player.rect.height;
                    float platformTop = platform->rect.top;
                    float deltaY = playerBottom - platformTop;
    
                    if (deltaY > 0 && deltaY < COLLISION_THRESHOLD) {
                        player.onGround = true;
                        player.rect.top = platformTop - player.rect.height;
                        player.dy = 0;
                        player.rect.left += platform->dx * time;
                    }
                }
            }
    
            if (auto* platform = dynamic_cast<VerticalMovingPlatform*>(entity)) {
                if (player.rect.intersects(platform->rect)) {
                    float playerBottom = player.rect.top + player.rect.height;
                    float platformTop = platform->rect.top;
                    float deltaY = playerBottom - platformTop;
    
                    if (deltaY > 0 && deltaY < COLLISION_THRESHOLD) {
                        player.onGround = true;
                        player.rect.top = platformTop - player.rect.height;
                        player.dy = 0;
                        player.rect.top += platform->dy * time;
                    }
                }
            }
            ++it;
        }
    
        // Drawing text and tiles
        camera.setCenter(
            player.rect.left + player.rect.width / 2,
            player.rect.top + player.rect.height / 2 - CAMERA_Y_OFFSET
        );
        window.setView(camera);
        hpText.setString("HP: " + std::to_string(player.health) + "/" + std::to_string(player.maxHealth));
        coinText.setString("Coins: " + std::to_string(player.coins));
        window.clear(sf::Color::White);
    
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == TILE_SOLID) rectangle.setFillColor(sf::Color::Black);
                if (TileMap[i][j] == TILE_EMPTY) continue;
                rectangle.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                window.draw(rectangle);
            }
        }
    
        for (auto& entity : entities) entity->draw(window);
        window.setView(uiView);
        window.draw(coinText);
        window.draw(weaponText);
        window.draw(hpText);
        window.display();
    }
    
    for (auto& entity : entities) {
        if (entity != &player) delete entity;
    }
    return 0;
}

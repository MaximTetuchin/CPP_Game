/*!
 * @file main.cpp
 * @brief Main game file containing the entry point and main game loop.
 * @author Maxim Tetuchin <tetuhin@inbox.ru | st128993@student.spbu.ru>
 * @version 1.0
 * @date 2025
 * 
 * @mainpage SFML Game Documentation
 * 
 * @section intro_sec Introduction
 * A 2D platformer with action elements, developed in C++ using SFML.
 * The player can navigate through levels, collect bonuses, fight enemies, and use various weapons.
 */

#include "source/Constants.h"
#include "source/Gameplay_objects/Tilemap.h"
#include "source/Entity.h"
#include "source/Gameplay_objects/Coin.h"
#include "source/Gameplay_objects/MovingPlatform.h"
#include "source/Gameplay_objects/VerticalMovingPlatform.h"
#include "source/Gameplay_objects/WinBlock.h"
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

/*! @brief Global vector containing all game entities */
std::vector<Entity*> entities; 

/*! @brief Main texture for game assets */
sf::Texture basicAssets;  

/*! @brief Rectangle for debugging and temporary calculations */
sf::RectangleShape rectangle(sf::Vector2f(32, 32));

/*!
 * @brief Main game function, program entry point.
 * 
 * Initializes the window, loads resources, creates game objects, and starts the main game loop.
 * @return Program exit code (0 on success)
 */
int main() {
    sf::Clock clock; ///< Timer for measuring time between frames
    sf::View uiView; ///< View for the user interface
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dakaraima!", sf::Style::Titlebar | sf::Style::Close);
    window.setSize(sf::Vector2u(800, 600));
    uiView.setSize(window.getSize().x, window.getSize().y); 
    uiView.setCenter(window.getSize().x / 2, window.getSize().y / 2);

    sf::View camera; ///< Camera for displaying the game world
    camera.setSize(720, 540);
    camera.setCenter(400, 300);
    window.setView(camera);

    // Load background
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/background.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundTexture.setRepeated(true);
    backgroundTexture.setRepeated(true);
    backgroundSprite.setTextureRect(sf::IntRect(0, 0, W * 32, H * 32));
    backgroundSprite.setPosition(0, -250);

    // Load fonts
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        return EXIT_FAILURE;
    }
    
    // Initialize UI text elements
    sf::Text coinText, weaponText, hpText;
    hpText.setFont(font); hpText.setCharacterSize(24);
    hpText.setFillColor(sf::Color::Red); hpText.setPosition(10, 80);

    coinText.setFont(font); coinText.setCharacterSize(24);
    coinText.setFillColor(sf::Color::Red); coinText.setPosition(10, 45);

    weaponText.setFont(font); weaponText.setCharacterSize(24); 
    weaponText.setFillColor(sf::Color::Red); weaponText.setPosition(10, 10);

    // Load main resources
    sf::Texture playerTex, bulletTex, basicAssets;
    sf::IntRect tileTex(80, 208, 32, 32);
    basicAssets.loadFromFile("assets/World-Tiles.png");
    playerTex.loadFromFile("assets/fang.png");
    bulletTex.loadFromFile("assets/fang.png");

    // Load tile textures
    sf::Sprite tileSprite;
    tileSprite.setTexture(basicAssets);
    tileSprite.setTextureRect(sf::IntRect(80, 417, 32, 32));
    tileSprite.setOrigin(0, 0);

    // Initialize enemy textures
    sf::Texture WalkingEnemyTex, ArmoredWalkingEnemyTex;
    WalkingEnemyTex.loadFromFile("assets/edited_assets/walkingEnemy.png");
    ArmoredWalkingEnemyTex.loadFromFile("assets/edited_assets/armoredWalkingEnemy.png");
    
    sf::Texture FlyingEnemyTex, ArmoredFlyingEnemyTex;
    FlyingEnemyTex.loadFromFile("assets/edited_assets/flyingEnemy.png");
    ArmoredFlyingEnemyTex.loadFromFile("assets/edited_assets/armoredFlyingEnemy.png");
    
    sf::Texture JumpingEnemyTex, ArmoredJumpingTex;
    JumpingEnemyTex.loadFromFile("assets/edited_assets/jumpingEnemy.png");
    ArmoredJumpingTex.loadFromFile("assets/edited_assets/armoredJumpingEnemy.png");
    
    // Initialize weapons
    Pistol pistol; Minigun minigun; Shotgun shotgun; Rifle rifle;
    pistol.setBulletTexture(bulletTex); minigun.setBulletTexture(bulletTex);
    shotgun.setBulletTexture(bulletTex); rifle.setBulletTexture(bulletTex);

    // Create player
    Player player(playerTex, &pistol);
    player.setPosition(150, 300);
    entities.push_back(&player);
    weaponText.setString("Weapon: " + player.currentWeapon->getName());

    // Create game objects based on tilemap
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            // Regular enemies
            if (TileMap[i][j] == 'E') {
                entities.push_back(new WalkingEnemy(WalkingEnemyTex, j*32, i*32, 34, 45, 0.060f, 100.0f));
                TileMap[i][j] = ' ';
            }
            if (TileMap[i][j] == 'F') {
                entities.push_back(new FlyingEnemy(FlyingEnemyTex, j * 32, i * 32, 42, 42, 0.055f, 100.0f));
                TileMap[i][j] = ' ';
            }
            if (TileMap[i][j] == 'J') {
                entities.push_back(new JumpingEnemy(JumpingEnemyTex, j*32, i*32, 39, 45, 0.065f, 100.0f, 0.3f));
                TileMap[i][j] = ' ';
            }     
            
            // Armored enemies
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
            
            // Game objects
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
            if (TileMap[i][j] == 'Q') {
                entities.push_back(new WinBlock(basicAssets, j*32, i*32));
                TileMap[i][j] = ' ';
            }
        }
    }

    // Main game loop
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
    
        // Input handling
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
            player.dx = -BASE_MOVE_SPEED * player.speedMultiplier;
            
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
            player.dx = BASE_MOVE_SPEED * player.speedMultiplier;

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
    
        // Weapon selection
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
    
        // Update all entities
        for (auto it = entities.begin(); it != entities.end();) {
            Entity* entity = *it;
            entity->update(time);
            
            // Handle bullet collisions
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
            
            // Handle enemies
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
            
            // Handle coins
            if (auto* coin = dynamic_cast<Coin*>(entity)) {
                if (player.rect.intersects(coin->rect)) {
                    player.addCoins(COIN_VALUE);
                    delete coin;
                    it = entities.erase(it);
                    continue;
                }
            }
            
            // Handle medkits
            if (auto* medkit = dynamic_cast<MedKit*>(entity)) {
                if (player.rect.intersects(medkit->rect)) {
                    player.health = std::min(player.health + HEAL_AMOUNT, player.maxHealth);
                    delete medkit;
                    it = entities.erase(it);
                    continue;
                }
            }
    
            // Handle invincibility spheres
            if (auto* invincibilitySphere = dynamic_cast<InvincibilitySphere*>(entity)) {
                if (player.rect.intersects(invincibilitySphere->rect)) {
                    player.isInvincible = true;
                    player.invincibilityTime = INVINCIBILITY_DURATION;
                    delete invincibilitySphere;
                    it = entities.erase(it);
                    continue;
                }
            }
    
            // Handle speed berries
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

            // Handle win block
            if (auto* winBlock = dynamic_cast<WinBlock*>(entity)) {
                if (player.rect.intersects(winBlock->rect)) {
                    sf::Text winText;
                    winText.setFont(font);
                    winText.setString("You win!");
                    winText.setCharacterSize(50);
                    winText.setFillColor(sf::Color::Green);
                    
                    winText.setPosition(camera.getCenter().x - 100, camera.getCenter().y - 50);
                    
                    window.setView(camera);
                    window.draw(winText);
                    window.display();
                    
                    sf::sleep(sf::seconds(3));
                    window.close();
                }
            }
            
            // Handle moving platforms
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
    
            // Handle vertically moving platforms
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
    
        // Update camera
        float camX = player.rect.left + player.rect.width / 2;
        float camY = player.rect.top + player.rect.height / 2 - CAMERA_Y_OFFSET;

        // Camera constraints
        if (camX < window.getSize().x / 2) camX = window.getSize().x / 2;
        if (camY < window.getSize().y / 2) camY = window.getSize().y / 2;
        if (camX > W * 32 - window.getSize().x / 2) camX = W * 32 - window.getSize().x / 2;
        if (camY > H * 32 - window.getSize().y / 2) camY = H * 32 - window.getSize().y / 2;

        camera.setCenter(camX, camY-32);
        
        // Rendering
        window.setView(camera);
        hpText.setString("HP: " + std::to_string(player.health) + "/" + std::to_string(player.maxHealth));
        coinText.setString("Coins: " + std::to_string(player.coins));
        window.clear(sf::Color::White);

        window.draw(backgroundSprite);
    
        // Render tiles
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == TILE_GRASS) {
                    sf::Sprite tileSprite(basicAssets);
                    tileSprite.setTextureRect(sf::IntRect(1, 417, 32, 32));
                    tileSprite.setPosition(j * 32, i * 32);
                    window.draw(tileSprite);
                }
                else if (TileMap[i][j] == TILE_GROUND) {
                    sf::Sprite tileSprite(basicAssets);
                    tileSprite.setTextureRect(sf::IntRect(2, 428, 32, 32));
                    tileSprite.setPosition(j * 32, i * 32);
                    window.draw(tileSprite);
                }
            }
        }
        
        // Render all entities
        for (auto& entity : entities) entity->draw(window);
        
        // Render UI
        window.setView(uiView);
        window.draw(coinText);
        window.draw(weaponText);
        window.draw(hpText);
        window.display();
    }
    
    // Cleanup resources
    for (auto& entity : entities) {
        if (entity != &player) delete entity;
    }

    return 0;
}
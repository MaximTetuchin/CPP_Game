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


//! --------------------------------------------- Main function ---------------------------------------------
int main() {
    sf::View uiView;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dakaraima!", sf::Style::Titlebar | sf::Style::Close);
    window.setSize(sf::Vector2u(800, 600));
    uiView.setSize(window.getSize().x, window.getSize().y); 
    uiView.setCenter(window.getSize().x / 2, window.getSize().y / 2);

    sf::View camera;
    camera.setSize(720, 540);
    camera.setCenter(400, 300);
    window.setView(camera);
    //! load font
    sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text coinText,weaponText,hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(24);
    hpText.setFillColor(sf::Color::Black);
    hpText.setPosition(10, 80);

    coinText.setFont(font);
    coinText.setCharacterSize(24);
    coinText.setFillColor(sf::Color::Black);
    coinText.setPosition(10, 45);

    weaponText.setFont(font);
    weaponText.setCharacterSize(24); 
    weaponText.setFillColor(sf::Color::Black);
    weaponText.setPosition(10, 10);

    //! ----------------------- basic assets ----------------------------
    sf::Texture playerTex, bulletTex,basicAssets;
    basicAssets.loadFromFile("assets/World-Tiles.png");
    playerTex.loadFromFile("assets/fang.png");
    bulletTex.loadFromFile("assets/fang.png");
    //! ----------------------- walking enemy ----------------------------
    sf::Texture WalkingEnemyTex,ArmoredWalkingEnemyTex;
    WalkingEnemyTex.loadFromFile("assets/edited_assets/walkingEnemy.png");
    ArmoredWalkingEnemyTex.loadFromFile("assets/edited_assets/armoredWalkingEnemy.png");
    //! ----------------------- flying enemy ----------------------------
    sf::Texture FlyingEnemyTex,ArmoredFlyingEnemyTex;
    FlyingEnemyTex.loadFromFile("assets/edited_assets/flyingEnemy.png");
    ArmoredFlyingEnemyTex.loadFromFile("assets/edited_assets/armoredFlyingEnemy.png");
    //! ----------------------- jumping enemy ----------------------------
    sf::Texture JumpingEnemyTex,ArmoredJumpingTex;
    JumpingEnemyTex.loadFromFile("assets/edited_assets/jumpingEnemy.png");
    ArmoredJumpingTex.loadFromFile("assets/edited_assets/armoredJumpingEnemy.png");
    //! ------------------------------ Weapons ----------------------------
    Pistol pistol;Minigun minigun;Shotgun shotgun;Rifle rifle;
    pistol.setBulletTexture(bulletTex);
    minigun.setBulletTexture(bulletTex);
    shotgun.setBulletTexture(bulletTex);
    rifle.setBulletTexture(bulletTex);

    Player player(playerTex, &pistol);
    std::vector<Entity*> entities;
    entities.push_back(&player);
    weaponText.setString("Weapon: " + player.currentWeapon->getName());

    //! Enemies spawn, after spawning an enemy, game creates an empty space in spawn. point
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

    sf::RectangleShape rectangle(sf::Vector2f(32, 32));
    sf::Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 700;
        if (time > 20) time = 20;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //! -------------------------- Keyboard actions --------------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
            player.dx = -0.1f * player.speedMultiplier;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
            player.dx = 0.1f * player.speedMultiplier;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.onGround) {
            player.dy = -0.35;
            player.onGround = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (player.currentWeapon && player.currentWeapon->tryFire(entities, 
                    player.rect.left + (player.lastAction ? 40 : -10),
                    player.rect.top + 10,
                    player.lastAction)) { 
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            player.switchWeapon(&pistol);
            weaponText.setString("Weapon: " + player.currentWeapon->getName());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            player.switchWeapon(&minigun);
            weaponText.setString("Weapon: " + player.currentWeapon->getName());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            player.switchWeapon(&shotgun);
            weaponText.setString("Weapon: " + player.currentWeapon->getName());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
            player.switchWeapon(&rifle);
            weaponText.setString("Weapon: " + player.currentWeapon->getName());
        }


        //! -------------------------- Game cycle logic --------------------------
        for (auto it = entities.begin(); it != entities.end();) {
            Entity* entity = *it;
            entity->update(time);

            if (auto* bullet = dynamic_cast<Bullet*>(entity)) {
                bool bulletHit = false;
                for (auto* enemy : entities) {
                    if (auto* enemyPtr = dynamic_cast<Enemy*>(enemy)) {
                         //! Bullet collision logic
                        if (enemyPtr->isAlive && bullet->rect.intersects(enemyPtr->rect)) {
                            enemyPtr->takeDamage(bullet->damage);
                            bulletHit = true;
                            break;
                        }
                    }
                }
                //! if bullet hits an entity, bullet disappears
                if (bulletHit || !bullet->isAlive) {
                    delete bullet;
                    it = entities.erase(it);
                    continue;
                }
            }
            //! if entity is alive, it draws on a map
            if (auto* enemy = dynamic_cast<Enemy*>(entity); enemy && !enemy->isAlive) {
                delete enemy;
                it = entities.erase(it);
                continue;
            }
            //! coins collision
            if (auto* coin = dynamic_cast<Coin*>(entity)) {
                if (player.rect.intersects(coin->rect)) {
                    player.addCoins(1);
                    std::cout<<"coin added\n";
                    delete coin; 
                    it = entities.erase(it);
                    continue;
                }
            }
            if (auto* medkit = dynamic_cast<MedKit*>(entity)) {
                if (player.rect.intersects(medkit->rect)) {
                    player.health = std::min(player.health + 35, player.maxHealth);
                    std::cout << "Health restored!\n";
                    delete medkit;
                    it = entities.erase(it);
                    continue;
                }
            }
            if (auto* invincibilitySphere = dynamic_cast<InvincibilitySphere*>(entity)) {
                if (player.rect.intersects(invincibilitySphere->rect)) {
                    player.isInvincible = true;
                    player.invincibilityTime = 5000.0f;
                    std::cout << "Invincibility activated!\n";
                    delete invincibilitySphere;
                    it = entities.erase(it);
                    continue;
                }
            }
            if (auto* speedBerry = dynamic_cast<SpeedBerry*>(entity)) {
                if (player.rect.intersects(speedBerry->rect)) {
                    player.speedMultiplier = 1.25f;
                    player.speedBoostTime = 10000.0f;
                    player.isSpeedBoosted = true;
                    delete speedBerry;
                    it = entities.erase(it);
                    continue;
                }
            }
            ++it;
        }
        for (auto* entity : entities) {
            if (auto* platform = dynamic_cast<MovingPlatform*>(entity)) {
                if (player.rect.intersects(platform->rect)) {
                    float playerBottom = player.rect.top + player.rect.height;
                    float platformTop = platform->rect.top;
                    float deltaY = playerBottom - platformTop;


                    if (deltaY > 0 && deltaY < 10) { 
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

                    if (deltaY > 0 && deltaY < 10) { 
                        player.onGround = true;
                        player.rect.top = platformTop - player.rect.height;
                        player.dy = 0;
                        player.rect.top += platform->dy * time;
                    }
                }
            }
            if (auto* enemy = dynamic_cast<Enemy*>(entity)) {
                if(enemy->isAlive && player.rect.intersects(enemy->rect)) {
                    player.takeDamage(20); 
                }
            }
            
        }
        

        camera.setCenter(player.rect.left + player.rect.width / 2,
                            player.rect.top + player.rect.height / 2 - 70);
        window.setView(camera);

        hpText.setString("HP: " + std::to_string(player.health) + "/" + std::to_string(player.maxHealth));
        coinText.setString("Coins: " + std::to_string(player.coins));
        window.clear(sf::Color::White);


        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == 'B') rectangle.setFillColor(sf::Color::Black);
                if (TileMap[i][j] == ' ') continue;
                rectangle.setPosition(j * 32, i * 32);
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

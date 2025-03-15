#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
using namespace sf;

const int H = 12;
const int W = 45;

//! My idea is to create a game engine.
String TileMap[H] = {
    "                                             ",
    "B                                           B",
    "B                                B          B",
    "B                 V                         B",
    "B                           E               B",
    "B         0000         BBBBBBBBBBB          B",
    "B                                B          B",
    "BBB                              B          B",
    "B              BB                BB         B",
    "B              BB         J                 B",
    "B    B         BB         BB           D    B", 
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};

//! Main class
class Entity {
public:
    Sprite sprite;
    FloatRect rect;
    float dx, dy;
    bool isAlive;

    Entity(Texture &image, float x, float y, float w, float h)
        : rect(x, y, w, h), dx(0), dy(0), isAlive(true) {
        sprite.setTexture(image);
    }

    virtual void update(float time) = 0;
    
    virtual void draw(RenderWindow &window) {
        sprite.setPosition(rect.left, rect.top);
        window.draw(sprite);
    }
};

//! --------------------------------------------- Weapons ---------------------------------------------
class Bullet : public Entity {
    public:
        float speed;
        bool direction;
        int damage;

        Bullet(Texture &image, float x, float y, bool dir, float spd, int dmg)
            : Entity(image, x, y, 8, 8), direction(dir), speed(spd), damage(dmg) {
            sprite.setTextureRect(IntRect(247, 583, 8, 8));
        }

        void update(float time) override {
            rect.left += speed * time * (direction ? 1 : -1);
        
            int i = rect.top / 32;
            int j = rect.left / 32;
        
            if (TileMap[i][j] == 'B') {
                isAlive = false;
            }
        
            if (rect.left < 0 || rect.left > W * 32) isAlive = false;
    }        
};

class Weapon {
    float fireDelay;
    float currentDelay;

    public:
        Texture bulletTexture;
        Weapon(float delay) 
            : fireDelay(delay), currentDelay(0) {}

        void setBulletTexture(Texture &texture) {
            bulletTexture = texture;
        }

        bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) {
            if (currentDelay <= 0) {
                bullets.push_back(new Bullet(bulletTexture,
                    x + (direction ? 6 : -6),
                    y + 6,
                    direction,
                    0.5f,
                    25));
                currentDelay = fireDelay;
                return true;
            }
            return false;
        }
        

        void update(float time) {
            if(currentDelay > 0) currentDelay -= time;
    }
};

class Player : public Entity {
public:
    bool onGround;
    float currentFrame;
    float idleFrame;
    bool lastAction;
    Weapon weapon;

    Player(Texture &image, Weapon &weapon)
        : Entity(image, 7*32, 9*32, 40, 50),
          weapon(weapon),
          onGround(false),
          currentFrame(0),
          lastAction(true) {}

    void update(float time) override {
        rect.left += dx * time;
        Collision(0);

        if(!onGround) dy += 0.0005 * time;
        rect.top += dy * time;
        onGround = false;
        Collision(1);

        currentFrame += 0.005 * time;
        idleFrame = currentFrame / 1.5;

        if(currentFrame > 6) currentFrame -= 6;
        if(idleFrame > 3) idleFrame -= 3;

        if(dx > 0) {
            sprite.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50));
            lastAction = true;
        } 
        else if(dx < 0) {
            sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 244, -40, 50));
            lastAction = false;
        } 
        else {
            if(lastAction) {
                sprite.setTextureRect(IntRect(43 * int(idleFrame) + 4, 188, 40, 50));
            } else {
                sprite.setTextureRect(IntRect(43 * int(idleFrame) + 4 + 40, 188, -40, 50));
            }
        }

        weapon.update(time);
        dx = 0;
    }

    void shoot(std::vector<Entity*>& bullets) {
        Bullet* newBullet = new Bullet(
            weapon.bulletTexture,
            rect.left + (lastAction ? 40 : -10),
            rect.top + 10, lastAction,
            0.5f, 25);
        bullets.push_back(static_cast<Entity*>(newBullet));
    }
    

    void Collision(int dir) {
        for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
            for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
                if (TileMap[i][j] == 'B') {
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
};
//! Basic enemy class
class Enemy : public Entity {
    public:
        int armor;
        int health;
        float speed;
        float moveRange;
        float startX;
        bool isAlive;
    
        Enemy(Texture &image, float x, float y, float w, float h, int armor, float speed, float range)
        : Entity(image, x, y, w, h), armor(armor), health(100), speed(speed), 
          moveRange(range), startX(x), isAlive(true) {}
    
        virtual void takeDamage(int damage) {
            int actualDamage = damage - armor;
            if (actualDamage < 0) actualDamage = 0;
            health -= actualDamage;
            std::cout << "Health: " << health << ", Armor: " << armor << std::endl;
            if (health <= 0) isAlive = false;
        }
    
        virtual void update(float time) = 0;
        virtual void Collision(int dir) = 0;
};
//! --------------------------------------------- Main enemy types ---------------------------------------------
class WalkingEnemy : public Enemy {
public:
    bool onGround;
    WalkingEnemy(Texture &image, float x, float y, float w, float h, float speed, float range)
        : Enemy(image, x, y, w, h, 0, speed, range), onGround(false) { // armor = 0
        sprite.setTextureRect(IntRect(0, 0, 34, 45));
    }

    void update(float time) override {
        float nextX = rect.left + speed * time;
    
        if (nextX < startX - moveRange || nextX > startX + moveRange) {
            speed = -speed;
            nextX = rect.left + speed * time;
        }

        rect.left = nextX;
        Collision(0);
    
        if(!onGround) dy += 0.0005 * time;
        rect.top += dy * time;
        onGround = false;
        Collision(1);
    }

    void Collision(int dir) override {
        for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
            for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
                if (TileMap[i][j] == 'B') {
                    if ((speed > 0) && (dir == 0)) rect.left = j * 32 - rect.width;
                    if ((speed < 0) && (dir == 0)) rect.left = j * 32 + 32;
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
            }
    }
};
class JumpingEnemy : public WalkingEnemy {
    private:
        float jumpTimer;
        float jumpInterval;
        float jumpForce;
    
    public:
        JumpingEnemy(Texture &image, float x, float y, float w, float h, 
                    float speed, float range, float jumpForce = 0.35f)
            : WalkingEnemy(image, x, y, w, h, speed, range), // armor = 0
              jumpForce(jumpForce) {
            jumpInterval = rand() % 3000 + 2000;
            jumpTimer = jumpInterval;
            sprite.setTextureRect(IntRect(0, 0, 39, 45));  //todo redo the texture
        }
    
        void update(float time) override {
            jumpTimer -= time;
            
            if(jumpTimer <= 0 && onGround) {
                dy = -jumpForce;
                onGround = false;

                jumpInterval = rand() % 3000 + 2000;
                jumpTimer = jumpInterval;
            }
    
            WalkingEnemy::update(time);
        }
};   
class FlyingEnemy : public Enemy {
public:
    FlyingEnemy(Texture &image, float x, float y, float w, float h, float speed, float range)
        : Enemy(image, x, y, w, h, 0, speed, range) { // armor = 0
        sprite.setTextureRect(IntRect(0, 0, 42, 42));
    }

    void update(float time) override {
        float nextX = rect.left + speed * time;
    
        if (nextX < startX - moveRange || nextX > startX + moveRange) {
            speed = -speed;
            nextX = rect.left + speed * time;
        }
    
        rect.left = nextX;
        Collision(0);
    }

    void Collision(int dir) override {
        if (dir == 0) {
            for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++) {
                for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
                    if (TileMap[i][j] == 'B') {
                        if (speed > 0) rect.left = j * 32 - rect.width;
                        else if (speed < 0) rect.left = j * 32 + 32;
                    }
                }
            }
        }
    }
};

//! --------------------------------------------- Armored Enemy Types ---------------------------------------------
class ArmoredWalkingEnemy : public WalkingEnemy {
    public:
        ArmoredWalkingEnemy(Texture &image, float x, float y, float w, float h, float speed, float range)
        : WalkingEnemy(image, x, y, w, h, speed, range) {
            armor = 10; // armor = 10
            sprite.setTextureRect(IntRect(0, 0, 34, 45));
        }
};
    
class ArmoredJumpingEnemy : public JumpingEnemy {
public:
    ArmoredJumpingEnemy(Texture &image, float x, float y, float w, float h, float speed, float range, float jumpForce = 0.35f)
        : JumpingEnemy(image, x, y, w, h, speed, range, jumpForce) {
            armor = 10; // armor = 10
            sprite.setTextureRect(IntRect(0, 0, 39, 45));
        }
};

class ArmoredFlyingEnemy : public FlyingEnemy {
public:
    ArmoredFlyingEnemy(Texture &image, float x, float y, float w, float h, float speed, float range)
        : FlyingEnemy(image, x, y, w, h, speed, range) {
            armor = 10; // armor = 10
            sprite.setTextureRect(IntRect(0, 0, 47, 45));
        }
};

//! --------------------------------------------- Main function ---------------------------------------------
int main() {
    RenderWindow window(VideoMode(800, 600), "Dakaraima!", Style::Titlebar | Style::Close);
    window.setSize(Vector2u(800, 600));

    View camera;
    camera.setSize(720, 540);
    camera.setCenter(400, 300);
    window.setView(camera);

    //! ----------------------- basic assets ----------------------------
    Texture playerTex, bulletTex;
    playerTex.loadFromFile("assets/fang.png");
    bulletTex.loadFromFile("assets/fang.png");
    //! ----------------------- walking enemy ----------------------------
    Texture WalkingEnemyTex,ArmoredWalkingEnemyTex;
    WalkingEnemyTex.loadFromFile("assets/edited_assets/walkingEnemy.png");
    ArmoredWalkingEnemyTex.loadFromFile("assets/edited_assets/armoredWalkingEnemy.png");
    //! ----------------------- flying enemy ----------------------------
    Texture FlyingEnemyTex,ArmoredFlyingEnemyTex;
    FlyingEnemyTex.loadFromFile("assets/edited_assets/flyingEnemy.png");
    ArmoredFlyingEnemyTex.loadFromFile("assets/edited_assets/armoredFlyingEnemy.png");
    //! ----------------------- jumping enemy ----------------------------
    Texture JumpingEnemyTex,ArmoredJumpingTex;
    JumpingEnemyTex.loadFromFile("assets/edited_assets/jumpingEnemy.png");
    ArmoredJumpingTex.loadFromFile("assets/edited_assets/armoredJumpingEnemy.png");

    Weapon weapon(200.0f);
    weapon.setBulletTexture(bulletTex);
    Player player(playerTex, weapon);

    std::vector<Entity*> entities;
    entities.push_back(&player);

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
        }
    }

    RectangleShape rectangle(Vector2f(32, 32));
    Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 700;
        if (time > 20) time = 20;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        //! -------------------------- Keyboard actions --------------------------
        if (Keyboard::isKeyPressed(Keyboard::Left)) player.dx = -0.1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) player.dx = 0.1;
        if (Keyboard::isKeyPressed(Keyboard::Up) && player.onGround) {
            player.dy = -0.35;
            player.onGround = false;
        }

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (player.weapon.tryFire(entities, player.rect.left + (player.lastAction ? 40 : -10),
                                        player.rect.top + 10, player.lastAction)) {
            }
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

            ++it;
        }

        camera.setCenter(player.rect.left + player.rect.width / 2,
                            player.rect.top + player.rect.height / 2 - 70);
        window.setView(camera);
        window.clear(Color::White);

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == 'B') rectangle.setFillColor(Color::Black);
                if (TileMap[i][j] == '0') rectangle.setFillColor(Color::Green);
                if (TileMap[i][j] == ' ') continue;
                rectangle.setPosition(j * 32, i * 32);
                window.draw(rectangle);
            }
        }

        for (auto& entity : entities) entity->draw(window);
        window.display();
    }

    for (auto& entity : entities) {
        if (entity != &player) delete entity;
    }
    return 0;
}

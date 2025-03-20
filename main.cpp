#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
using namespace sf;

const int H = 12;
const int W = 45;

//! My idea is to create a game engine.
String TileMap[H] = {
    "                                             ",
    "B                                H          B",
    "B                                B          B",
    "B                 V                         B",
    "B          C                                B",
    "B         BBBB         BBBBBBBBBBB          B",
    "B                                B          B",
    "BBB                              BI         B",
    "B       L      BB                BB         B",
    "B              BB    U    J                 B",
    "B    B         BB         BB    S      D    B", 
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};

//! Main 
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
std::vector<Entity*> entities; 
Texture basicAssets;  
//! ------------------------------------------- Stuct entity --------------------------------------------
class Coin : public Entity {
    public:
        Coin(Texture &image, float x, float y) 
            : Entity(image, x, y, 7, 8) {
            sprite.setTextureRect(IntRect(4, 1348, 7, 8)); 
        }
        void update(float time) override {} 
};

//! ------------------------------------------- Moving platforms -----------------------------------------
class MovingPlatform : public Entity {
    private:
        float moveRange;
        float startX;
        float speed;
        bool movingRight;
    
    public:
        MovingPlatform(Texture &image, float x, float y, float w, float h, float range, float spd)
            : Entity(image, x, y, w, h), moveRange(range), speed(spd), movingRight(true) {
            startX = x;
            sprite.setTextureRect(IntRect(1, 417, 64, 16));
        }
    
        void update(float time) override {
            float nextX = rect.left + (movingRight ? speed : -speed) * time;
    
            if (nextX > startX + moveRange) {
                movingRight = false;
                nextX = startX + moveRange;
            } else if (nextX < startX - moveRange) {
                movingRight = true;
                nextX = startX - moveRange;
            }
    
            rect.left = nextX;
            dx = (movingRight ? 2*speed : -2*speed);
    }
};

class VerticalMovingPlatform : public Entity {
    private:
        float moveRange; 
        float startY; 
        float speed;   
        bool movingDown; 
    
    public:
        VerticalMovingPlatform(Texture &image, float x, float y, float w, float h, float range, float spd)
            : Entity(image, x, y, w, h), moveRange(range), speed(spd), movingDown(true) {
            startY = y; 
            sprite.setTextureRect(IntRect(1, 417, 64, 16));
        }
    
        void update(float time) override {
            float nextY = rect.top + (movingDown ? speed : -speed) * time;
    
            if (nextY > startY + moveRange) {
                movingDown = false; 
                nextY = startY + moveRange;
            } else if (nextY < startY - moveRange) {
                movingDown = true;
                nextY = startY - moveRange;
            }
    
            rect.top = nextY;
            dy = (movingDown ? speed : -speed); 
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
    public:
        virtual ~Weapon() = default;
        virtual bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) = 0;
        virtual void update(float time) = 0;
        virtual void setBulletTexture(Texture& texture) = 0;
        virtual std::string getName() const = 0;
};

class Pistol : public Weapon {
    private:
        float fireDelay;
        float currentDelay;
        Texture bulletTexture;
        int damage;
    
    public:
        Pistol(float delay = 420.0f, int dmg = 25)
            : fireDelay(delay), currentDelay(0), damage(dmg) {}
    
        void setBulletTexture(Texture& texture) override {
            bulletTexture = texture;
        }
        
        std::string getName() const override {
            return "Pistol";
        }
    
        bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) override {
            if (currentDelay <= 0) {
                bullets.push_back(new Bullet(bulletTexture,
                    x + (direction ? 6 : -6),
                    y + 6,
                    direction,
                    0.5f,
                    damage));
                currentDelay = fireDelay;
                return true;
            }
            return false;
        }
    
        void update(float time) override {
            if (currentDelay > 0) currentDelay -= time;
    }
};
class Minigun : public Weapon {
    private:
        float fireDelay;
        float currentDelay;
        Texture bulletTexture;
        int damage;
        int bulletsPerShot;
    
    public:
        Minigun(float delay = 150.0f, int dmg = 11, int bullets = 3)
            : fireDelay(delay), currentDelay(0), damage(dmg), bulletsPerShot(bullets) {}
    
        void setBulletTexture(Texture& texture) override {
            bulletTexture = texture;
        }

        std::string getName() const override {
            return "Minigun";
        }
    
        bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) override {
            if (currentDelay <= 0) {
                for (int i = 0; i < bulletsPerShot; i++) {
                    bullets.push_back(new Bullet(bulletTexture,
                        x + (direction ? 6 : -6),
                        y + 6 + (i * 3),
                        direction,
                        0.5f + (i * 0.1f),
                        damage));
                }
                currentDelay = fireDelay;
                return true;
            }
            return false;
        }
    
        void update(float time) override {
            if (currentDelay > 0) currentDelay -= time;
        }
};
class Shotgun : public Weapon {
    private:
        float fireDelay;
        float currentDelay;
        Texture bulletTexture;
        int damage;
        int pelletCount;
    
    public:
        Shotgun(float delay = 2000.0f, int dmg = 55, int pellets = 2)
            : fireDelay(delay), currentDelay(0), damage(dmg), pelletCount(pellets) {}
    
        void setBulletTexture(Texture& texture) override {
            bulletTexture = texture;
        }

        std::string getName() const override {
            return "Shotgun";
        }
    
        bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) override {
            if (currentDelay <= 0) {
                for (int i = 0; i < pelletCount; i++) {
                    bullets.push_back(new Bullet(bulletTexture,
                        x + (direction ? 6 : -6),
                        y + 6 + (i * 5),
                        direction,
                        0.5f + (i * 0.1f),
                        damage));
                }
                currentDelay = fireDelay;
                return true;
            }
            return false;
        }
    
        void update(float time) override {
            if (currentDelay > 0) currentDelay -= time;
        }
};

class Rifle : public Weapon {
    private:
        float fireDelay;
        float currentDelay;
        Texture bulletTexture;
        int damage;
    
    public:
        Rifle(float delay = 200.0f, int dmg = 18)
            : fireDelay(delay), currentDelay(0), damage(dmg) {}
    
        void setBulletTexture(Texture& texture) override {
            bulletTexture = texture;
        }
    
        bool tryFire(std::vector<Entity*>& bullets, float x, float y, bool direction) override {
            if (currentDelay <= 0) {
                bullets.push_back(new Bullet(bulletTexture,
                    x + (direction ? 6 : -6),
                    y + 6,
                    direction,
                    0.7f,
                    damage));
                currentDelay = fireDelay;
                return true;
            }
            return false;
        }
    
        void update(float time) override {
            if (currentDelay > 0) currentDelay -= time;
        }
    
        std::string getName() const override {
            return "Rifle";
        }
};

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
    bool isInvincible;

    float speedMultiplier;
    float speedBoostTime;
    bool isSpeedBoosted;

    Player(Texture& image, Weapon* startingWeapon)
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
          isInvincible(false) {} 

    void addCoins(int amount) {
        coins += amount;
    }

    void takeDamage(int damage) {
        if(!isInvincible) {
            health -= damage;
            std::cout<<"damage was taken!!!!!!!!!!!!!!!\n";
            if(health < 0) health = 0;
            invincibilityTime = 1500.0f;
            isInvincible = true;
        }
    }

    void switchWeapon(Weapon* newWeapon) {
        currentWeapon = newWeapon;
    }

    void update(float time) override {
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
            sprite.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50));
            lastAction = true;
        } 
        else if (dx < 0) {
            sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 244, -40, 50));
            lastAction = false;
        } 
        else {
            if (lastAction) {
                sprite.setTextureRect(IntRect(43 * int(idleFrame) + 4, 188, 40, 50));
            } else {
                sprite.setTextureRect(IntRect(43 * int(idleFrame) + 4 + 40, 188, -40, 50));
            }
        }

        if (currentWeapon) {
            currentWeapon->update(time);
        }
        dx = 0;
    };

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
//! Basic enemy
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
            : WalkingEnemy(image, x, y, w, h, speed, range),
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
        : Enemy(image, x, y, w, h, 0, speed, range) {
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
            armor = 10;
            sprite.setTextureRect(IntRect(0, 0, 34, 45));
        }
};
    
class ArmoredJumpingEnemy : public JumpingEnemy {
public:
    ArmoredJumpingEnemy(Texture &image, float x, float y, float w, float h, float speed, float range, float jumpForce = 0.35f)
        : JumpingEnemy(image, x, y, w, h, speed, range, jumpForce) {
            armor = 10;
            sprite.setTextureRect(IntRect(0, 0, 39, 45));
        }
};

class ArmoredFlyingEnemy : public FlyingEnemy {
public:
    ArmoredFlyingEnemy(Texture &image, float x, float y, float w, float h, float speed, float range)
        : FlyingEnemy(image, x, y, w, h, speed, range) {
            armor = 10;
            sprite.setTextureRect(IntRect(0, 0, 47, 45));
        }
};
//! --------------------------------------------- Extra mechanics -------------------------------------------
class MedKit : public Entity {
    public:
        MedKit(Texture &image, float x, float y) 
            : Entity(image, x, y, 7, 6) { 
            sprite.setTextureRect(IntRect(100, 693, 7, 6)); 
        }
        void update(float time) override {}
};
class InvincibilitySphere : public Entity {
    public:
        InvincibilitySphere(Texture &image, float x, float y) 
            : Entity(image, x, y, 5, 5) {
            sprite.setTextureRect(IntRect(5, 902, 5, 5));
        }
        void update(float time) override {}
};
class SpeedBerry : public Entity {
    public:
        SpeedBerry(Texture &image, float x, float y) 
            : Entity(image, x, y, 10, 9) {
            sprite.setTextureRect(IntRect(36, 311, 10, 9));
        }
        void update(float time) override {}
}; 
//! --------------------------------------------- Main function ---------------------------------------------
int main() {
    View uiView;
    RenderWindow window(VideoMode(800, 600), "Dakaraima!", Style::Titlebar | Style::Close);
    window.setSize(Vector2u(800, 600));
    uiView.setSize(window.getSize().x, window.getSize().y); 
    uiView.setCenter(window.getSize().x / 2, window.getSize().y / 2);

    View camera;
    camera.setSize(720, 540);
    camera.setCenter(400, 300);
    window.setView(camera);
    //! load font
    Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        return EXIT_FAILURE;
    }

    Text coinText,weaponText,hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(24);
    hpText.setFillColor(Color::Black);
    hpText.setPosition(10, 80);

    coinText.setFont(font);
    coinText.setCharacterSize(24);
    coinText.setFillColor(Color::Black);
    coinText.setPosition(10, 45);

    weaponText.setFont(font);
    weaponText.setCharacterSize(24); 
    weaponText.setFillColor(Color::Black);
    weaponText.setPosition(10, 10);

    //! ----------------------- basic assets ----------------------------
    Texture playerTex, bulletTex,basicAssets;
    basicAssets.loadFromFile("assets/World-Tiles.png");
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
        if (Keyboard::isKeyPressed(Keyboard::Left)) 
            player.dx = -0.1f * player.speedMultiplier;

        if (Keyboard::isKeyPressed(Keyboard::Right)) 
            player.dx = 0.1f * player.speedMultiplier;

        if (Keyboard::isKeyPressed(Keyboard::Up) && player.onGround) {
            player.dy = -0.35;
            player.onGround = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            if (player.currentWeapon && player.currentWeapon->tryFire(entities, 
                    player.rect.left + (player.lastAction ? 40 : -10),
                    player.rect.top + 10,
                    player.lastAction)) { 
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Num1)) {
            player.switchWeapon(&pistol);
            weaponText.setString("Weapon: " + player.currentWeapon->getName());
        }
        if (Keyboard::isKeyPressed(Keyboard::Num2)) {
            player.switchWeapon(&minigun);
            weaponText.setString("Weapon: " + player.currentWeapon->getName());
        }
        if (Keyboard::isKeyPressed(Keyboard::Num3)) {
            player.switchWeapon(&shotgun);
            weaponText.setString("Weapon: " + player.currentWeapon->getName());
        }
        if (Keyboard::isKeyPressed(Keyboard::Num4)) {
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
        window.clear(Color::White);


        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == 'B') rectangle.setFillColor(Color::Black);
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

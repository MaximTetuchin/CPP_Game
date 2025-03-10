#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

const int H = 12;
const int W = 40;

String TileMap[H] = {
    "                                        ",
    "B                                      B",
    "B                                B     B",
    "B                                      B",
    "B                                      B",
    "B         0000                BBBB     B",
    "B                                B     B",
    "BBB                              B     B",
    "B              BB                BB    B",
    "B              BB                      B",
    "B    B         BB         BB      E    B", // Enemy at position (32, 10)
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};

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

class Bullet : public Entity {
public:
    float speed;
    bool direction;
    int damage;

    Bullet(Texture &image, float x, float y, bool dir, float spd, int dmg)
        : Entity(image, x, y, 10, 10), direction(dir), speed(spd), damage(dmg) {}

    void update(float time) override {
        rect.left += speed * time * (direction ? 1 : -1);
        if (rect.left < 0 || rect.left > W*32) isAlive = false;
    }
};

class Weapon {
    Texture bulletTexture;
    float fireDelay;
    float currentDelay;
    
	public:
    Weapon(const String &texturePath, float delay) 
        : fireDelay(delay), currentDelay(0) {
        bulletTexture.loadFromFile(texturePath);
    }

    bool tryFire(std::vector<Bullet*> &bullets, float x, float y, bool direction) {
        if(currentDelay <= 0) {
            bullets.push_back(new Bullet(bulletTexture,
                x + (direction ? 40 : -10), 
                y + 15, direction, 
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

    Player(Texture &image) 
        : Entity(image, 7*32, 9*32, 40, 50),
          weapon("assets/bullet.png", 200.0f),
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
        idleFrame = currentFrame/1.5;

        if(currentFrame > 6) currentFrame -= 6;
        if(idleFrame > 3) idleFrame -= 3;

        if(dx > 0) {
            sprite.setTextureRect(IntRect(40*int(currentFrame), 244, 40, 50));
            lastAction = true;
        } 
        else if(dx < 0) {
            sprite.setTextureRect(IntRect(40*int(currentFrame)+40, 244, -40, 50));
            lastAction = false;
        } 
        else {
            if(lastAction) {
                sprite.setTextureRect(IntRect(43*int(idleFrame)+4, 188, 40, 50));
            } else {
                sprite.setTextureRect(IntRect(43*int(idleFrame)+4 + 40, 188, -40, 50));
            }
        }

        weapon.update(time);
        dx = 0;
    }

    void shoot(std::vector<Bullet*> &bullets) {
        weapon.tryFire(bullets, rect.left, rect.top, lastAction);
    }

    void Collision(int dir) {
        for (int i = rect.top/32; i < (rect.top + rect.height)/32; i++)
            for (int j = rect.left/32; j < (rect.left + rect.width)/32; j++) {
                if (TileMap[i][j] == 'B') {
                    if ((dx > 0) && (dir == 0)) rect.left = j*32 - rect.width;
                    if ((dx < 0) && (dir == 0)) rect.left = j*32 + 32;
                    if ((dy > 0) && (dir == 1)) { 
                        rect.top = i*32 - rect.height; 
                        dy = 0; 
                        onGround = true; 
                    }
                    if ((dy < 0) && (dir == 1)) { 
                        rect.top = i*32 + 32; 
                        dy = 0; 
                    }
                }
                if (TileMap[i][j] == '0') TileMap[i][j] = ' ';
            }
    }
};

class Enemy : public Entity {
public:
    int armor;
    bool onGround;
    int health;
    float speed;
    float moveRange; // Range within which the enemy moves
    float startX;    // Starting X position

    Enemy(Texture &image, float x, float y, float w, float h, int armor, float speed, float range)
        : Entity(image, x, y, w, h), armor(armor), health(100), speed(speed), moveRange(range), startX(x),onGround(false) {}

    void takeDamage(int damage) {
        health -= (damage - armor);
        if (health <= 0) isAlive = false;
    }

    void update(float time) override {
        // Move back and forth within the range
        if (rect.left < startX - moveRange || rect.left > startX + moveRange) {
            speed = -speed; // Reverse direction
        }
        rect.left += speed * time;

        // Handle collisions
        Collision(0);

        if(!onGround) dy += 0.0005 * time;
        rect.top += dy * time;
        onGround = false;
        Collision(1);
    }

    void Collision(int dir) {
        for (int i = rect.top/32; i < (rect.top + rect.height)/32; i++)
            for (int j = rect.left/32; j < (rect.left + rect.width)/32; j++) {
                if (TileMap[i][j] == 'B') {
                    if ((speed > 0) && (dir == 0)) rect.left = j*32 - rect.width;
                    if ((speed < 0) && (dir == 0)) rect.left = j*32 + 32;
                    if ((dy > 0) && (dir == 1)) { 
                        rect.top = i*32 - rect.height; 
                        dy = 0; 
                        onGround = true; 
                    }
                    if ((dy < 0) && (dir == 1)) { 
                        rect.top = i*32 + 32; 
                        dy = 0; 
                    }
                }
            }
    }
};

int main() {
    RenderWindow window(VideoMode(800, 600), "Dakaraima!", Style::Titlebar | Style::Close);
    window.setSize(Vector2u(800, 600));

    View camera;
    camera.setSize(720, 540);
    camera.setCenter(400, 300);
    window.setView(camera);

    Texture playerTex;
    playerTex.loadFromFile("assets/fang.png");

    Texture enemyTex;
    enemyTex.loadFromFile("assets/enemy.png");

    Player player(playerTex);
    std::vector<Bullet*> bullets;
    std::vector<Enemy*> enemies;

    // Parse TileMap for enemies
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (TileMap[i][j] == 'E') {
                enemies.push_back(new Enemy(enemyTex, j * 32, i * 32, 40, 50, 5, 0.05f, 100.0f)); // Armor = 5, Speed = 0.05, Range = 100
                TileMap[i][j] = ' '; // Remove 'E' from the map after creating the enemy
            }
        }
    }

    RectangleShape rectangle(Vector2f(32,32));
    Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 700;
        if(time > 20) time = 20;

        Event event;
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed)
                window.close();
        }

        if(Keyboard::isKeyPressed(Keyboard::Left)) {
            player.dx = -0.1;
        }

        if(Keyboard::isKeyPressed(Keyboard::Right)) {
            player.dx = 0.1;
        }

        if(Keyboard::isKeyPressed(Keyboard::Up)) {
            if(player.onGround) {
                player.dy = -0.35; 
                player.onGround = false;
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Space)) {
            player.shoot(bullets);
        }

        player.update(time);

        for (auto& enemy : enemies) {
            enemy->update(time);
        }

        for(auto it = bullets.begin(); it != bullets.end();) {
            (*it)->update(time);

            bool bulletHit = false;
            for (auto& enemy : enemies) {
                if (enemy->isAlive && (*it)->rect.intersects(enemy->rect)) {
                    enemy->takeDamage((*it)->damage);
                    bulletHit = true;
                    break;
                }
            }

            if (bulletHit || !(*it)->isAlive) {
                delete *it;
                it = bullets.erase(it);
            } else {
                ++it;
            }
        }

        camera.setCenter(player.rect.left + player.rect.width/2, 
                        player.rect.top + player.rect.height/2 - 70);
        window.setView(camera);
        window.clear(Color::White);

        for(int i = 0; i < H; i++) {
            for(int j = 0; j < W; j++) {
                if(TileMap[i][j] == 'B') rectangle.setFillColor(Color::Black);
                if(TileMap[i][j] == '0') rectangle.setFillColor(Color::Green);
                if(TileMap[i][j] == ' ') continue;

                rectangle.setPosition(j*32, i*32);
                window.draw(rectangle);
            }
        }

        for(auto &bullet : bullets) {
            bullet->draw(window);
        }

        player.draw(window);

        // Draw enemies
        for (auto& enemy : enemies) {
            if (enemy->isAlive) enemy->draw(window);
        }

        window.display();
    }

    for(auto &bullet : bullets) delete bullet;
    for(auto &enemy : enemies) delete enemy;
    return 0;
}
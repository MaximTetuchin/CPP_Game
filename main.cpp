#include <SFML/Graphics.hpp>

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
"B    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
}; 

/*-----------------------------------Alive entity logic------------------------------------*/
//! Entity class
class Entity {
	public:
		Sprite sprite;
		FloatRect rect;
		float dx, dy;
		bool isAlive;
	
		Entity(Texture &image, float x, float y, float w, float h) {
			sprite.setTexture(image);
			rect = FloatRect(x, y, w, h);
			dx = dy = 0;
			isAlive = true;
		}
	
		virtual void update(float time) = 0;
	
		void draw(RenderWindow &window) {
			sprite.setPosition(rect.left, rect.top);
			window.draw(sprite);
		}
};

//! Player class
class Player : public Entity {
	public:
		bool onGround;
		//! Animation fields
		float currentFrame;
		float idleFrame;
		bool lastAction; //! i enter this field to understand at which direction player is currently looking.
		//! 1 - forward, 0 - backward	

		Player(Texture &image) : Entity(image, 7 * 32, 9 * 32, 40, 50) {
			onGround = false;
			currentFrame = 0;
			lastAction = 1;
		}
	
		void update(float time) override {
			rect.left += dx * time;
			Collision(0);
		
			if (!onGround) dy += 0.0005 * time;
			rect.top += dy * time;
			onGround = false;
			Collision(1);
		
			currentFrame += 0.005 * time;
			idleFrame = currentFrame/1.5; //! idle animation must be slower than the original one, i think so..

			if (currentFrame > 6) currentFrame -= 6;
			if (idleFrame > 3) idleFrame -= 3; 

			if (dx > 0) {
				sprite.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50));
			} else if (dx < 0) {
				sprite.setTextureRect(IntRect(40 * int(currentFrame) + 40, 244, -40, 50));
			} else if (dx == 0) {
				if (lastAction){
					sprite.setTextureRect(IntRect(43 * int(idleFrame)+4, 188, 40, 50));
				} else {
					sprite.setTextureRect(IntRect(43 * int(idleFrame)+4 + 40, 188, -40, 50));
				}
			}
		
			sprite.setPosition(rect.left, rect.top);
			dx = 0;
		}
				
		void Collision(int dir) {
			for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
				for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
					if (TileMap[i][j] == 'B') {
						if ((dx > 0) && (dir == 0)) rect.left = j * 32 - rect.width;
						if ((dx < 0) && (dir == 0)) rect.left = j * 32 + 32;
						if ((dy > 0) && (dir == 1)) { rect.top = i * 32 - rect.height; dy = 0; onGround = true; }
						if ((dy < 0) && (dir == 1)) { rect.top = i * 32 + 32; dy = 0; }
					}
					if (TileMap[i][j] == '0'){
						TileMap[i][j] = ' ';
					}
				}
		}
};		

/*----------------------------------------Guns logic---------------------------------------*/
class Bullet : public Entity {
	public:
		float speed;
		int damage;
	
		Bullet(Texture &image, float x, float y, bool lastAction, float spd, int dmg) 
			: Entity(image, x, y, 10, 10) {
			int direction = lastAction ? 1 : -1; // Направление в зависимости от того, куда смотрит игрок
			speed = spd * direction; 
			damage = dmg;  // Урон пули, передаваемый при создании
		}
	
		void update(float time) override {
			rect.left += speed * time;
			if (rect.left < 0 || rect.left > 800) {
				isAlive = false; // Пуля исчезает, если выходит за экран
			}
			sprite.setPosition(rect.left, rect.top);
		}
};
	
class Weapon {
public:
	float fireRate; 
	Texture bulletTexture1, bulletTexture2;
	bool hasTwoBulletTypes;
	int shotCount;
	
	//! one-type bullet weapon
	Weapon(float rate, const String &bulletTex) 
		: fireRate(rate), hasTwoBulletTypes(false), shotCount(0) {
		bulletTexture1.loadFromFile(bulletTex);
	}

	//! two-type bullet weapon
	Weapon(float rate, const String &bulletTex1, const String &bulletTex2) 
		: fireRate(rate), hasTwoBulletTypes(true), shotCount(0) {
		bulletTexture1.loadFromFile(bulletTex1);
		bulletTexture2.loadFromFile(bulletTex2);
	}

	//! shoot method
	void shoot(std::vector<Entity*> &entities, float x, float y, bool lastAction) {
		Texture &selectedTexture = bulletTexture1; 
		float bulletSpeed = 0.3;
		int bulletDamage = 10;

		//! in case if fire bullet
		if (hasTwoBulletTypes && (shotCount % 5 == 1)) {
			selectedTexture = bulletTexture2;
			bulletSpeed = 0.4;
			bulletDamage = 15; 
		}
		entities.push_back(new Bullet(selectedTexture, x, y, lastAction, bulletSpeed, bulletDamage));
		shotCount++;
	}
};	

int main()
{   
	//! window and camera creation
    RenderWindow window(VideoMode(800, 600), "Dakaraima!", sf::Style::Titlebar | sf::Style::Close);
	window.setSize(Vector2u(800, 600));
    View camera;
    camera.setSize(720,540);
    camera.setCenter(400, 300);
    window.setView(camera);

	//! texture creation
	Texture t;
	t.loadFromFile("assets/fang.png");

	Clock clock;
	float currentFrame=0;

    Player p(t); //! player init.
	RectangleShape rectangle(Vector2f(32,32)); //! tile init.

	//! window cycle
    while (window.isOpen()) {

		//! FPS drop protection
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 700;
		if (time > 20) time = 20;

		//! keyboard handler
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
	
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			p.dx = -0.1;
			p.lastAction = 0;
		}
	
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.dx = 0.1;
			p.lastAction = 1;
		}
	
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (p.onGround) { p.dy = -0.35; p.onGround = false; }
		}
		
		//! player cond. update
		p.update(time);
	
		//! camera update
		camera.setCenter(p.rect.left + p.rect.width / 2, p.rect.top + p.rect.height / 2-70);
		window.setView(camera);
		window.clear(Color::White);
		
		//! map creation
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++) {
				if (TileMap[i][j] == 'B') rectangle.setFillColor(Color::Black);
				if (TileMap[i][j] == '0') rectangle.setFillColor(Color::Green);
				if (TileMap[i][j] == ' ') continue;
	
				rectangle.setPosition(j * 32, i * 32);
				window.draw(rectangle);
			}
		
		//! sprite draw
		window.draw(p.sprite);

		//! frame display
		window.display();
	}

    return 0;
}
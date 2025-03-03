#include <SFML/Graphics.hpp>

using namespace sf;

const int H = 12;
const int W = 40;

String TileMap[H] = {

"B                                       ",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B                                B     B",
"B         0000                BBBB     B",
"B                                B     B",
"BBB                              B     B",
"B              BB                BB    B",
"B              BB                      B",
"B    B         BB         BB           B",
"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",

}; 

class PLAYER {

	public:
		float dx,dy;
		FloatRect rect;
		bool onGround;
		Sprite sprite;
		float currentFrame;

	public:
		PLAYER(Texture &image)
	{
		sprite.setTexture(image);
		rect = FloatRect(7*32,9*32,40,50);
		dx=dy=0.1;
		currentFrame = 0;
	}


	void update(float time)
	{	

		rect.left += dx * time;	
		Collision(0);

		if (!onGround) dy=dy+0.0005*time;
		rect.top += dy*time;
		onGround=false;
		Collision(1);
	
		
		currentFrame += 0.005*time;
		if (currentFrame > 6) currentFrame -=6 ;

		if (dx>0) sprite.setTextureRect(IntRect(40*int(currentFrame),244,40,50));
		if (dx<0) sprite.setTextureRect(IntRect(40*int(currentFrame)+40,244,-40,50));
		

		sprite.setPosition(rect.left, rect.top);

		dx=0;
	}



	void Collision(int dir)
	{
		for (int i = rect.top/32 ; i<(rect.top+rect.height)/32; i++)
		for (int j = rect.left/32; j<(rect.left+rect.width)/32; j++)
			{ 
			if (TileMap[i][j]=='B') 
			{ 
				if ((dx>0) && (dir==0)) rect.left =  j*32 -  rect.width; 
				if ((dx<0) && (dir==0)) rect.left =  j*32 + 32;
				if ((dy>0) && (dir==1))  { rect.top =   i*32 -  rect.height;  dy=0;   onGround=true; }
				if ((dy<0) && (dir==1))  { rect.top = i*32 + 32;   dy=0;}
			}
			
			if (TileMap[i][j]=='0') 
							{ 
								TileMap[i][j]=' ';
							}
					
			}
	
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

    PLAYER p(t); //! player init.
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
		}
	
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.dx = 0.1;
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
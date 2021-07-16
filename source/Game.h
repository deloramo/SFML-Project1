#pragma once

#include "Player.h"
#include "Sandbag.h"
#include "Barrel.h"

class Game
{
private:
	//Required class objects for game
	Player* player;
	Player* player2;
	Barrel* barrels;
	Sandbag* sandbags;
	BulletList* bullets;
	//Coordinates for barrel and sandbag
	Coord* objCoor;

	const sf::Vector2i res; //Width and height
	sf::Vector2f fRes; //type float of width and height
	sf::RenderWindow* window;
	sf::Event event;
	sf::Texture bgTexture;
	sf::Sprite bgSprite; //Sprites
	sf::Sprite sprite; 
	int is[3];

	//Font, text
	sf::Font font;
	sf::Text text;

	//Marks move-keys pressed and values them
	int setCounterUp;
	int setCounterDown;
	int setCounterRight;
	int setCounterLeft;

	//Private functions
	void checkOpen();
	void updatePlayer1();
	void updatePlayer2();
	void updateBullets();
	void updateScore();
	void drawBg();
	void drawSoldier();
	void drawBullet();
	void checkCollision(const Coord&, Player*); 
	void preventCollision(float, Player*);
	void setMove(int, Player*);

	int st;//Movement state, moving where or not moving at all
	int p1_bTimer = 0;
	int p2_bTimer = 0;
	bool timer_p1;
	bool timer_p2;
public:
	//Constructor / Destructor
	Game();
	~Game();

	//Functions
	void updateActivity();
	void render(); //Draws background, objects and displays them

	void drawSandBag();
	void drawBarrel();

		//Run state
	const bool isRunning() const;
};


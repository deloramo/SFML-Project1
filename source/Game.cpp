#include "Game.h"


//Constructor 
Game::Game() : res(1024, 768), st(-1), is{ 5,6,7 } //Init res & state for movement
{
	//Init window
	window = new sf::RenderWindow(sf::VideoMode(res.x, res.y), "Game Window", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);

	//Init background texture
	if (!bgTexture.loadFromFile("grass.png"))
		std::cout << "ERROR: Background Texture Not Found" << std::endl;

	//Init bg sprite (texture is repeadet not stretched)
	bgTexture.setRepeated(true);
	bgTexture.setSmooth(true);
	bgSprite.setTexture(bgTexture);
	bgSprite.setTextureRect({ 0, 0, res.x, res.y });

	//new Player object, basically convert int to float, set position
	player = new Player;
	player2 = new Player(2);
	fRes = window->mapPixelToCoords(sf::Vector2i(1024, 768));
	player->setPos(fRes.x / 2 - 40.f, fRes.y - 100.f);
	player2->setPos(fRes.x / 2 - 40.f, -12.f);

	//barrel and sb alloced
	barrels = new Barrel;
	sandbags = new Sandbag;

	//Alloc coord for barrel and sandbag
	objCoor = new Coord[8]; 

	//Set coords for bar and sb 
	for (int i = 0; i < 8; ++i) {
		objCoor[i].x = static_cast<float>((100 + i * 200) % 1024);
		objCoor[i].y = static_cast<float>((200 + i * 100) % 768);
	}

	//Bullet list
	bullets = new BulletList;
	bullets->setWindow(window);
	bullets->objects = objCoor;
	bullets->is = is;

	//Set player sprite and get its bounds
	sprite.setTexture(player->getTexture());
	
	player->bounds = sprite.getLocalBounds();
	player->boundary = fRes;
	
	player2->bounds = sprite.getLocalBounds();
	player2->boundary = fRes;

	//Font
	if (!font.loadFromFile("font.ttf"))
		std::cout << "Error: Font Not Loaded";
	text.setFont(font);
	text.setPosition(500.f, 700.f);
}

//Destructor, deallocs dynamically alloced memory on heap
Game::~Game()
{
	delete window;
	delete player;
	delete barrels;
	delete sandbags;
	delete bullets;
	delete[] objCoor;
}

void Game::checkCollision(const Coord& p, Player* player)//Checks collision state 
{
	for (int i = 0; i < 5; ++i) {//For sandbag
		if (player->getPos().x + 50.f >= objCoor[i].x && player->getPos().x <= objCoor[i].x + 30.f && player->getPos().y <= objCoor[i].y + 15.f && player->getPos().y + 60.f >= objCoor[i].y)
		{
			preventCollision(player->getMoveBy(), player); 
		}
	}
	
	for (int i : is) {//For barrel
		if (i == 0)
			continue;

		if (player->getPos().x + 45.f >= objCoor[i].x && player->getPos().x <= objCoor[i].x + 20.f && player->getPos().y <= objCoor[i].y - 5.f && player->getPos().y + 60.f >= objCoor[i].y)
		{
			preventCollision(player->getMoveBy(), player);
		}
	}
}

void Game::preventCollision(float temp, Player* player)//Prevents collision from happening
{
	switch (st)
	{
	case -1:
		return;
	case 0:
		player->movePos(0, temp);
		return;
	case 1:
		player->movePos(0, -temp);
		return;
	case 2:
		player->movePos(-temp, 0);
		return;
	case 3:
		player->movePos(temp, 0);
		return;
	}
}

void Game::checkOpen()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}

//Functions - private
void Game::updatePlayer1()
{
	if (timer_p1 == true) {
		p1_bTimer++;
		if (p1_bTimer == 20) {
			p1_bTimer = 0;
			timer_p1 = false;
		}
	}
	//Check if fire bullet
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && timer_p1 == false) {
		bullets->add(player->getPos(), player->getState());
		timer_p1 = true;
	}

	//Implementing a nice, smooth move-style
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		++setCounterUp;
	}
	else {
		setCounterUp = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		++setCounterDown;
	}
	else {
		setCounterDown = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		++setCounterRight;
	}
	else {
		setCounterRight = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		++setCounterLeft;
	}
	else {
		setCounterLeft = 0;
	}
	int minExZer[4] = { setCounterUp, setCounterDown, setCounterRight, setCounterLeft };
	int minEZ;
	bool chosen = false;
	st = -1;

	for (int i = 0; i < 4; ++i)
	{
		if (minExZer[i] != 0) {
			if (chosen == false) {
				minEZ = minExZer[i];
				st = i;
				chosen = true;
			}
			else if (minEZ > minExZer[i]) {
				st = i;
				minEZ = minExZer[i];
			}
		}
	}
	setMove(st + 1, player);
}

void Game::updatePlayer2()
{
	if (timer_p2 == true) {
		p2_bTimer++;
		if (p2_bTimer == 20) {
			p2_bTimer = 0;
			timer_p2 = false;
		}
	}
	//Check if fire bullet
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timer_p2 == false) {
		bullets->add(player2->getPos(), player2->getState());
		timer_p2 = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		++setCounterUp;
	}
	else {
		setCounterUp = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		++setCounterDown;
	}
	else {
		setCounterDown = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		++setCounterRight;
	}
	else {
		setCounterRight = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		++setCounterLeft;
	}
	else {
		setCounterLeft = 0;
	}
	int minExZer[4] = { setCounterUp, setCounterDown, setCounterRight, setCounterLeft };
	int minEZ;
	bool chosen = false;
	st = -1;

	for (int i = 0; i < 4; ++i)
	{
		if (minExZer[i] != 0) {
			if (chosen == false) {
				minEZ = minExZer[i];
				st = i;
				chosen = true;
			}
			else if (minEZ > minExZer[i]) {
				st = i;
				minEZ = minExZer[i];
			}
		}
	}
	setMove(st + 1, player2);
}

void Game::updateBullets()
{
	int a = bullets->update(player->getPos(), player2->getPos());
	if (a == 1) {
		player->setPos(fRes.x / 2 - 40.f, -12.f);
		player2->incrementScore();
	}
	if(a == 2) {
		player2->setPos(fRes.x / 2 - 40.f, fRes.y - 100.f);
		player->incrementScore();
	}
}

void Game::updateScore()
{
	int p1 = player->getScore();
	int p2 = player2->getScore();

	std::string a = std::to_string(p1);
	std::string b = std::to_string(p2);
	std::string c = " : ";
	text.setString(a + c + b);

}

void Game::drawBg() //Draw background
{
	window->draw(bgSprite);
}

void Game::drawSoldier()
{
	//P1
	sprite.setTexture(player->getTexture(),true);
	sprite.setPosition(player->getPos().x, player->getPos().y);
	window->draw(sprite);

	//P2
	sprite.setTexture(player2->getTexture());
	sprite.setPosition(player2->getPos().x, player2->getPos().y);
	window->draw(sprite);
}

void Game::drawBullet()
{
	bullets->draw();
}

//Functions for movement
void Game::setMove(int a, Player* player)
{
	if (a < 0 || a > 4)
		std::cout << "ERROR: CASE NOT FOUND" << std::endl;

	switch (a)
	{
	case 0:
		return;
	case 1:
		player->moveUp();
		checkCollision(player->getPos(), player);
		return;
	case 2:
		player->moveDown();
		checkCollision(player->getPos(), player);
		return;
	case 3:
		player->moveRight();
		checkCollision(player->getPos(), player);
		return;
	case 4:
		player->moveLeft();
		checkCollision(player->getPos(), player);
		return;
	}
}



void Game::drawSandBag()
{
	for (int i = 0; i < 5; ++i) {
		sprite.setTexture(sandbags->getTexture(), true);
		sprite.setPosition(objCoor[i].x, objCoor[i].y);
		window->draw(sprite);
	}
}

void Game::drawBarrel()
{
	for (int i : is) {
		if (i == 0)
			continue;

		sprite.setTexture(barrels->getTexture(), true);
		sprite.setPosition(objCoor[i].x, objCoor[i].y);
		window->draw(sprite);
	}
}
//Functions - public



void Game::updateActivity()//Game flow
{
	if (player->getScore() == 10) {
		text.setPosition(270.f, 300.f);

		text.setString("Player1 Won, go again?(Y/N)");
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
			player->setScore(0);
			player2->setScore(0);
			text.setPosition(500.f, 700.f);
			text.setString("0 : 0");
			for (int i = 0; i < 3; ++i) {
				if (is[i] == 0)
					is[i] = 5 + i;
			}
			player->setPos(fRes.x / 2 - 40.f, fRes.y - 100.f);
			player2->setPos(fRes.x / 2 - 40.f, -12.f);

			bullets->empty();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
			window->close();
		}
		return;
	}
	if (player2->getScore() == 10) {

		text.setPosition(270.f, 300.f);

		text.setString("Player2 Won, go again?(Y/N)");
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
			player->setScore(0);
			player2->setScore(0);
			text.setPosition(500.f, 700.f);
			text.setString("0 : 0");
			for (int i = 0; i < 3; ++i) {
				if (is[i] == 0)
					is[i] = 5 + i;
			}
			player->setPos(fRes.x / 2 - 40.f, fRes.y - 100.f);
			player2->setPos(fRes.x / 2 - 40.f, -12.f);

			bullets->empty();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
			window->close();
		
				 
		}
		return;
	}
	checkOpen();
	updatePlayer1();
	updatePlayer2();
	updateBullets();
	updateScore();
}

void Game::render() //draw and display
{
	drawBg();


	drawSandBag();
	drawBarrel();
	drawSoldier();
	drawBullet();
	window->draw(text);

	window->display();
}


//Run state
const bool Game::isRunning() const
{
	return window->isOpen();
}

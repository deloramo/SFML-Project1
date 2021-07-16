#include "Player.h"

//Constructor
Player::Player() : state(0), s(0), moveCounter(0), moveBy(4.f)
{
	//loop to init textures, sprites
	for (int i = 0; i < 14; ++i)
	{
		//a,b,c,d to prevent copy&paste, it's required to pass std::string type anyways
		std::string c, d, b = "soldier";
		c = std::to_string(i);
		d = ".png";
		const std::string a = b + c + d;
		if (!textures[i].loadFromFile(a))
			std::cout << "ERROR: Player Texture Not Found" << std::endl;

		textures[i].setSmooth(true);
	}
}

Player::Player(int) :s(0), moveCounter(0), moveBy(4.f)
{
	state = 4;
	//loop to init textures, sprites
	for (int i = 0; i < 14; ++i)
	{
		//a,b,c,d to prevent copy&paste, it's required to pass std::string type anyways
		std::string c, d, b = "soldier";
		c = std::to_string(i);
		d = ".png";
		const std::string a = b + c + d;
		if (!textures[i].loadFromFile(a))
			std::cout << "ERROR: Player Texture Not Found" << std::endl;

		textures[i].setSmooth(true);
	}
}

const sf::Texture& Player::getTexture() const//returns texture of current state 
{
	return textures[state];
}


//Player position functions
void Player::setPos(float x, float y)
{
	this->pos.x = x;

	this->pos.y = y;
}

void Player::movePos(float x, float y)
{
	if (this->pos.x + x - 10.f < boundary.x - bounds.width && this->pos.x + x + 5.f > 0)
		this->pos.x += x;
	if (this->pos.y + y - 5.f < boundary.y - bounds.height && this->pos.y + y + 10.f > 0)
		this->pos.y += y;
}

const Coord& Player::getPos() const
{
	return pos;
}

void Player::moveUp()
{
	if (!(moveCounter % 8)) { //Switch statements below are for move animation
		switch (state)
		{
		case 0:
			if (s == 0) {
				state = 7;
				s = 1;
			}

			else {
				state = 8;
				s = 0;
			}

			break;
		case 1:
			state = 0;
			break;
		case 2:
			state = 1;
			break;
		case 3:
			state = 2;
			break;
		case 4:
			state = 5;
			break;
		case 5:
			state = 6;
			break;
		case 6:
			state = 7;
			s = 1;
			break;
		case 7:
			state = 0;
			break;
		case 8:
			state = 0;
			break;
		case 9:
			state = 2;
			break;
		case 10:
			state = 2;
			break;
		case 11:
			state = 4;
			break;
		case 12:
			state = 6;
			break;
		case 13:
			state = 6;
			break;
		}
	}
	++moveCounter;
	movePos(0, -moveBy);
}

void Player::moveDown()
{
	if (!(moveCounter % 8))
	{
		switch (state)
		{
		case 0:
			state = 1;
			break;
		case 1:
			state = 2;
			break;
		case 2:
			state = 3;
			s = 1;
			break;
		case 3:
			state = 4;
			break;
		case 4:
			if (s == 0) {
				state = 3;
				s = 1;
			}
			else {
				state = 11;
				s = 0;
			}
			break;
		case 5:
			state = 4;
			break;
		case 6:
			state = 5;
			break;
		case 7:
			state = 6;
			break;
		case 8:
			state = 0;
			break;
		case 9:
			state = 2;
			break;
		case 10:
			state = 2;
			break;
		case 11:
			state = 4;
			break;
		case 12:
			state = 6;
			break;
		case 13:
			state = 6;
			break;
		}
	}
	++moveCounter;
	movePos(0, moveBy);
}

void Player::moveRight()
{
	if (!(moveCounter % 8)) {
		switch (state)
		{
		case 0:
			state = 1;
			break;
		case 1:
			state = 2;
			break;
		case 2:
			if (s == 0) {
				state = 10;
				s = 1;
			}
			else {
				state = 9;
				s = 0;
			}
			break;
		case 3:
			state = 2;
			break;
		case 4:
			state = 3;
			s = 1;
			break;
		case 5:
			state = 4;
			break;
		case 6:
			state = 5;
			break;
		case 7:
			state = 0;
			break;
		case 8:
			state = 0;
			break;
		case 9:
			state = 2;
			break;
		case 10:
			state = 2;
			break;
		case 11:
			state = 4;
			break;
		case 12:
			state = 6;
			break;
		case 13:
			state = 6;
			break;
		}
	}
	++moveCounter;
	movePos(moveBy, 0);
}

void Player::moveLeft()
{
	if (!(moveCounter % 8)) {
		switch (state)
		{
		case 0:
			state = 7;
			s = 1;
			break;
		case 1:
			state = 0;
			break;
		case 2:
			state = 1;
			break;
		case 3:
			state = 4;
			break;
		case 4:
			state = 5;
			break;
		case 5:
			state = 6;
			break;
		case 6:
			if (s == 1) {
				state = 12;
				s = 0;
			}
			else {
				state = 13;
				s = 1;
			}
			break;
		case 7:
			state = 6;
			break;
		case 8:
			state = 0;
			break;
		case 9:
			state = 2;
			break;
		case 10:
			state = 2;
			break;
		case 11:
			state = 4;
			break;
		case 12:
			state = 6;
			break;
		case 13:
			state = 6;
			break;
		}
	}
	++moveCounter;
	movePos(-moveBy, 0);
}

float Player::getMoveBy()
{
	return moveBy;
}

int Player::getState()
{
	return state;
}

void Player::incrementScore(void)
{
	++score;
}

int Player::getScore(void)
{
	return score;
}

void Player::setScore(int s)
{
	score = s;
}




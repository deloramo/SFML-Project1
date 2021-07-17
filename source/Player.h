#pragma once

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Coord.h"
#include "BulletList.h"


class Player : public Object
{
private:
	sf::Texture textures[14]; 
	//Game class manages sprites, so no sprite or window pointer declared here
	Coord pos;
	int state;
	int s;
	int moveCounter;
	float moveBy; //kinda move speed
	int score = 0;

public:
	sf::Vector2f boundary; //To not let soldier leave window, will be set by game class
	sf::FloatRect bounds;
	//Constructor 
	Player();
	//Overloaded constructor for settings
	Player(int);
	
	//Functions
	const sf::Texture& getTexture() const;
	void setPos(float, float);
	void movePos(float, float);
	const Coord& getPos() const;
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	float getMoveBy();
	int getState();
	void incrementScore(void);
	int getScore(void);
	void setScore(int);
};


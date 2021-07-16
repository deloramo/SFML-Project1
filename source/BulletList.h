#pragma once
#include "Bullet.h"
#include "Coord.h"
#include <iostream>

class BulletList
{
private:
	Bullet* head;
	Bullet* tail;
	sf::Sprite bulletSprite;
	sf::Texture bulletTextures[4];
	sf::RenderWindow* window;
	
	bool checkColl(int&, Bullet*, Coord, Coord); //if collide, return true
public:
	BulletList();
	~BulletList();//Destructor for dynamically alloced memory
	void add(Coord pos, int state);
	int update(Coord, Coord);
	void draw();
	void setWindow(sf::RenderWindow*);
	void empty();

	Coord* objects;
	int* is;
};


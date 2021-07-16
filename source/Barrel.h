#pragma once

#include "Coord.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Barrel : public Object
{
private:
	sf::Texture texture;
	Coord pos;
	int isVisible = 1;
public:
	Barrel();
	const sf::Texture& getTexture() const;
	Coord barGetPos();
	bool getVisible(void);
	void setVisible(bool visible);
};


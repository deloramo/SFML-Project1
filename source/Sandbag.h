#pragma once

#include "Coord.h"
#include <iostream>

class Sandbag : public Object
{
private:
	sf::Texture texture;
	Coord pos;
public:
	Sandbag();
	const sf::Texture& getTexture() const;
	void sbInit(float, float);
	Coord sBgetPos();
};


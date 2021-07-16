#include "Sandbag.h"

Sandbag::Sandbag()
{
	if(!texture.loadFromFile("bags.png")) 
	std::cout << "ERROR: SandBag Texture Not Found" << std::endl;

}

const sf::Texture & Sandbag::getTexture() const
{
	return texture;
}

void Sandbag::sbInit(float x, float y)
{
	this->pos.x = x;
	this->pos.y = y;
}

Coord Sandbag::sBgetPos()
{
	return pos;
}

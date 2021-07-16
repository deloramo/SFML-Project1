#include "Barrel.h"

Barrel::Barrel()
{
	if (!texture.loadFromFile("barrel.png"))
	std::cout << "ERROR: Barrel Texture Not Found" << std::endl;
}

const sf::Texture & Barrel::getTexture() const
{
	return texture;
}

Coord Barrel::barGetPos()
{
	return pos;
}

bool Barrel::getVisible(void)
{
	if (isVisible == 1)
		return true;
	return false;
}

void Barrel::setVisible(bool visible)
{
	if (visible)
		isVisible = 1;
	else
		isVisible = 0;
}

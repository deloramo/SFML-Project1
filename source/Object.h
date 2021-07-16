#pragma once
#include <SFML/Graphics.hpp>
class Object
{
private:
	sf::RenderWindow *window;
	sf::Sprite sprite;
	sf::Texture texture;
public:
	float x;
	float y;
	Object();
	void paint();
};


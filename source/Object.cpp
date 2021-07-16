#include "Object.h"

Object::Object()
{
	window = nullptr;
}

void Object::paint()
{
	window->draw(sprite);
}

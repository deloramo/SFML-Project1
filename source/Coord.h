#pragma once
#include "Object.h" //I think this class shouldn't inherit from object instead it should be the other way. But im doing what im asked to do so.
class Coord : public Object 
{
public:
	float x;
	float y;

public:
	Coord();
	Coord(float, float);
};


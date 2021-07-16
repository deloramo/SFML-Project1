#pragma once
#include "Object.h" 
class Coord : public Object 
{
public:
	float x;
	float y;

public:
	Coord();
	Coord(float, float);
};


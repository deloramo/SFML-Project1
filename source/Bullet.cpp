#include "Bullet.h"

Bullet::Bullet() : speed(10.f), next(nullptr)
{
}

void Bullet::move(void)
{
	switch (direction)
	{
	case 0:
		y -= speed;
		break;
	case 1:
		y += speed;
		break;
	case 2:
		x += speed;
		break;
	case 3:
		x -= speed;
		break;
	}
}

void Bullet::setSpeed(float speed)
{
	this->speed = speed;
}

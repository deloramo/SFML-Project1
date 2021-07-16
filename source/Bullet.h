#pragma once
#include "Object.h"
class Bullet : public Object
{
	friend class BulletList;
private:
	float speed;
	int direction;//0,1,2,3, -> up, down, right, left
	Bullet* next;
public:
	Bullet();
	void move(void);
	void setSpeed(float speed);
};


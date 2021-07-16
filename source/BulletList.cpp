#include "BulletList.h"


BulletList::BulletList() : head(nullptr), tail(nullptr), window(nullptr)
{
	for (int i = 0; i < 4; ++i)
	{
		std::string c, d, b = "bullet";
		c = std::to_string(i);
		d = ".png";
		const std::string a = b + c + d;
		if (!bulletTextures[i].loadFromFile(a))
			std::cout << "ERROR: Bullet Texture Not Found" << std::endl;

		bulletTextures[i].setSmooth(true);
	}
}

BulletList::~BulletList()
{
	Bullet* temp;
	while (head) {
		temp = head->next;
		delete head;
		head = temp;
	}
}

void BulletList::add(Coord pos, int state)
{
	if (state == 1 || state == 5)
		return;
	if (head == nullptr) {
		tail = new Bullet;
		head = tail;
	}
	else {
		tail->next = new Bullet;
		tail = tail->next;
	}
		tail->x = pos.x;
		tail->y = pos.y;
	
	if (state == 8 || state == 0 || state == 7) {
		tail->direction = 0;
		tail->x += 60.f; 
		return;
	}
	if (state == 9 || state == 2 || state == 10) {
		tail->direction = 2;
		tail->y += 75.f;
		tail->x += 80.f;
		return;
	}
	if (state == 11 || state == 4 || state == 3) {
		tail->direction = 1;
		tail->x += 28.f;
		tail->y += 90.f;
		return;
	}
	if (state == 12 || state == 6 || state == 13) {
		tail->direction = 3;
		tail->y += 38.f;
		tail->x -= 11.f;
		return;
	}
}

bool BulletList::checkColl(int& a, Bullet* b, Coord pos1, Coord pos2)
{
	
	//Boundary check
	if (b->x < -24 || b->y < -24 || b->y > 768 || b->x > 1024)
		return true;

	for (int i = 0; i < 5; ++i) {//For sandbag 
		if (b->x >= objects[i].x && b->x <= objects[i].x + 55.f && b->y <= objects[i].y + 65.f && b->y >= objects[i].y)
		{
			return true;
		}
	}


	for (int i = 0; i < 3; ++i) {//For barrel
		int x = is[i];
		if (x == 0)
			continue;

		if (b->x >= objects[x].x && b->x <= objects[x].x + 57.f && b->y <= objects[x].y + 57.f && b->y >= objects[x].y)
		{
			is[i] = 0;
			return true;
		}
	}

	if (b->x >= pos1.x && b->x <= pos1.x + 80.f && b->y <= pos1.y + 80.f && b->y >= pos1.y)//For Player1
	{
		a = 1;
		return true;
	}
	if (b->x >= pos2.x && b->x <= pos2.x + 80.f && b->y <= pos2.y + 80.f && b->y >= pos2.y)//For Player2
	{
		a = 2;
		return true;
	}
	return false;
}

int BulletList::update(Coord pos1, Coord pos2)
{
	int a = 0;
	Bullet* temp = head; 
	Bullet* prev = head;
	while (temp) {
		temp->move();
		if (checkColl(a, temp, pos1, pos2)) {
			if (head == tail) {
				delete temp;
				head = nullptr;
				tail = nullptr;
				temp = nullptr;
				continue;
			}
			if (temp == head) {
				head = head->next;
				delete temp;
				temp = head;
				prev = head;
				continue;
			}

			if (temp == tail) {
				tail = prev;
			}
			prev->next = temp->next;
			delete temp;
			temp = prev->next;
			continue;
		}
		prev = temp;
		temp = temp->next;
	}
	return a;
}

void BulletList::draw()
{
	Bullet* temp = head; 
	while (temp) {
		bulletSprite.setTexture(bulletTextures[temp->direction],true);
		bulletSprite.setPosition(temp->x, temp->y);
		window->draw(bulletSprite);

		temp = temp->next;
	}
}

void BulletList::setWindow(sf::RenderWindow * window)
{
	this->window = window;
}

void BulletList::empty()
{
	Bullet* temp;
	while (head) {
		temp = head->next;
		delete head;
		head = temp;
	}
}


#include "Boss.h"

Boss::Boss()
{
	if (!texture.loadFromFile("Sprites/boss.png"))
	{
		std::cout << "Fail to load" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sizeX, sizeY);
}

void Boss::SetLife(int newLife)
{
	life = newLife;
}

int Boss::GetLife()
{
	return life;
}

int Boss::GetMaxLife()
{
	return maxLife;
}

float Boss::GetSpeed()
{
	return speed;
}

void Boss::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

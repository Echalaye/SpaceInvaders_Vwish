#include "Monster.h"

Monster::Monster(std::string imgToLoad)
{
	if (!texture.loadFromFile((imgToLoad)))
	{
		std::cout << "Fail to load" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sizeX, sizeY);
}

float Monster::getSpeed()
{
	return speed;
}


void Monster::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Monster::setLife(int damage)
{
	life -= damage;
}

int Monster::getLife()
{
	return life;
}

float Monster::GetSpeedBoost()
{
	return speedBoost;
}

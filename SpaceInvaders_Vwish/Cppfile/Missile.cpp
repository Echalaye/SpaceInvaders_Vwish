#include "Missile.h"

Missile::Missile()
{
	if (!texture.loadFromFile("Sprites/player_missile.png"))
	{
		std::cout << "Fail to load" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sizeX, sizeY);
}



void Missile::SetDegat(int newDegat)
{
	degat = newDegat;
}

int Missile::getDamage()
{
	return degat;
}

float Missile::GetSpeed()
{
	return speed;
}

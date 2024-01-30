#include "CampementLife.h"

CampementLife::CampementLife()
{
	if (!texture.loadFromFile("Sprites/MaxLife.png"))
	{
		std::cout << "Fail to load" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sizeX, sizeY);
}


void CampementLife::SetDegatRecieveTexture()
{

	if (life == 6 && !texture.loadFromFile("Sprites/MidLife.png")  )
	{
		std::cout << "Fail to load" << std::endl;
	}
	if(life == 3 && !texture.loadFromFile("Sprites/LowLife.png")  )
	{
		std::cout << "Fail to load" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sizeX, sizeY);
}

int CampementLife::GetLife()
{
	return life;
}

void CampementLife::SetLife(int damage)
{
	life -= damage;
	SetDegatRecieveTexture();
}


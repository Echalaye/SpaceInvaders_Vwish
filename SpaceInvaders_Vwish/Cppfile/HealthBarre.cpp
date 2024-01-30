#include "HealthBarre.h"

HealthBarre::HealthBarre(std::string imageNamebck, std::string imageNameFront)
{
	if (!textureBck.loadFromFile(imageNamebck))
	{
		std::cout << "Fail to load" << std::endl;
	}
	spriteBck.setTexture(textureBck);
	spriteBck.setScale(sizeX, sizeY);

	if (!textureFront.loadFromFile(imageNameFront))
	{
		std::cout << "Fail to load" << std::endl;
	}
	spriteFront.setTexture(textureFront);
	spriteFront.setScale(sizeX, sizeY);
}

void HealthBarre::SetHealthBarre(int life, int lifeMax)
{
	spriteFront.setTextureRect(sf::IntRect(0, 0, int((float)life / (float)lifeMax * spriteBck.getGlobalBounds().width), spriteBck.getGlobalBounds().height));
}


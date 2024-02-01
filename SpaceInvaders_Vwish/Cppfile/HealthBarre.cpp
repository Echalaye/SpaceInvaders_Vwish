// HealthBarre.cpp est le script qui défini le comportement de la classe HealthBarre, il contient les fonction suivante:
//	- SetHealthBarre: qui prend deux paramètres, la vie actuel du joueur (ou du boss) et la vie maximum du joueur (ou du boss)
//	  elle permet de set la taille du sprite de la barre de vie et donc de créer une vrai barre de vie qui diminue
//	- HealthBarre : le constructeur qui sert a load sprite du background de la barre de vie ainsi que le sprite de la barre de vie
//	  il prend en paramètre les deux chemin d'image a utiliser car elle change en fonciton de la barre de vie pour le boss où le joueur

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


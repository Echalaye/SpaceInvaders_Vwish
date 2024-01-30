//	Monster.cpp est le script qui d�finie le comportement de la classe Monster, il contient les fonction suivante :
//	- getSpeed : fonction qui permet de r�cuperer la vitesse de d�placement des monstre
//	- setSpeed: fonction qui permet de d�finir la vitesse de d�placement des monstre
//	- setLife: fonction qui permet d'infliger des d�gats au monstre
//	- getLife: fonction qui permet de r�cuper la vie du monstre
//	- GetSpeedBoost: fonction qui permet d'obtenir la variable de bosst de vitesse des monstre
//	- Monster: fonction qui permet de load le sprite des monstre elle prend en param�tre un sprite car celui-ci change a chaque niveau

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

//	Monster.cpp est le script qui définie le comportement de la classe Monster, il contient les fonction suivante :
//	- getSpeed : fonction qui permet de récuperer la vitesse de déplacement des monstre
//	- setSpeed: fonction qui permet de définir la vitesse de déplacement des monstre
//	- setLife: fonction qui permet d'infliger des dégats au monstre
//	- getLife: fonction qui permet de récuper la vie du monstre
//	- GetSpeedBoost: fonction qui permet d'obtenir la variable de bosst de vitesse des monstre
//	- Monster: fonction qui permet de load le sprite des monstre elle prend en paramètre un sprite car celui-ci change a chaque niveau

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

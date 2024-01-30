// boss.cpp est le script qui défini le comportement de la classe Boss, il contient les fonction suivante:
//	- SetLife : permet de set la vie du boss
//	- GetLife: permet de récuperer la vie actuel du boss
//	- GetMaxLife: permet de récuperer la vie maximum du boss (utile pour la barre de vie)
//	- GetSpeed: permet de récupérer la vitesse de déplacement du boss
//	- Set Speed: permet de set la vitesse du boss
//	- Boss: constructeur, permet de load le sprite du Boss

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

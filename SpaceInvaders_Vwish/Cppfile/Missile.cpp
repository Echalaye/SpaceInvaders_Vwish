// Missile.cpp est le script qui définie le fonctionnement de la classe Missile, il contient les fonction suivante:
//	- SetDegat : permet de changer la valeur des degats d'un missile
//	- GetDamage : permet de récuperer les damage que le missile inflige
//	- GetSpeed : permet de récuperer la vitesse d'un missile
//	- Missile : le constructeur qui permet de load le sprite du missile

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

// CampementLife.cpp est le script qui d�fini le comportement de la classe CampementLife. On trouve les fonction suivante dans le script:
//	- GetLife : permet de r�cup�rer la vie du campement
//	- SetLife : permet d'infliger des d�gats au campement en envoyant en param�tre un d�gat. A la fin de la fonction elle appelle SetDegatRecieveTexture
//	- SetDegatRecieveTexture : Le campement poss�de trois texture diff�rente en fonction de sa vie, 
//	  cette fonction permet de changer la dite texture en fonction de la vie du campement.
//	- CampementLife : constructeur qui permet de load l'image de base du campement


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


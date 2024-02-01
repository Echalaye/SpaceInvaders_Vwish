// Button.cpp est le script qui défini le comportement de la classe Button, il contient les fonction suivante:
//	- SetIsActive : elle set la variable isActive qui permet d'autoriser la detection du clique
//	  sur le bouton a la valeur passer en paramètre
//	- GetIsActive : qui permet de récupérer la variable isActive 
//	- CheckButton : le constructeur qui sert a load sprite du Bouton.
//	  Le constructeur prend en paramètre l'image a utiliser pour le sprite du bouton

#include "Button.h"

Button::Button(std::string imageName)
{
	if (!texture.loadFromFile(imageName))
	{
		std::cout << "Fail to load" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sizeX, sizeY);
	tagButton = imageName;
}

bool Button::GetIsActive()
{
	return isActive;
}

void Button::SetIsActive(bool val)
{
	isActive = val;
}

bool Button::CheckButton(sf::Event::MouseButtonEvent& mouseEvent)
{
	sf::FloatRect mousePosition{(float)mouseEvent.x, (float)mouseEvent.y, 1.f, 1.f};

	if (sprite.getGlobalBounds().intersects(mousePosition))
	{
		return true;
	}

	return false;
}

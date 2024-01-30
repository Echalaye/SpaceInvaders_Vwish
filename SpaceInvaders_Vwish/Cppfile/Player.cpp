//Player.cpp, script de la classe Player, contient les fonction :
//	- GetMovementDirection : permet de d�finir la direction dans laquelle va le player et de la limit� au bordure de l'�cran
//	- SetLife : permet de red�finir la vie actuel du joueur (notament lorsqu'il prend des d�gats)
//	- GetLife et GetMaxLife: permette respectivement de r�cuperer la valeur life et maxLife du player.
//	- Player: Constructeur permet de load le sprite du player et de le set a la bonne taille.

#include "Player.h"



Player::Player()
{
	if (!texture.loadFromFile("Sprites/mec_qui_tire.png"))
	{
		std::cout << "Fail to load" << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(sizeX, sizeY);
}



float Player::GetMovementDirection(int valKey, sf::Sprite playerSprite, int screenSizeX)
{
	if (playerSprite.getPosition().x - 5.f > 0 && valKey == 0) {
		return -speed;
	}
	else if(valKey == 0) {
		return 0;
	}
	if (playerSprite.getPosition().x + 5.f + playerSprite.getScale().x + 50 < screenSizeX && valKey == 1) {
		return speed;
	}
	else if (valKey == 1){
		return 0;
	}
}

void Player::SetLife(int newLife)
{
	life = newLife;
}

int Player::GetLife()
{
	return life;
}

int Player::GetMaxLife()
{
	return maxLife;
}

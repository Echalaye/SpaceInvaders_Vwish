#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class HealthBarre
{
private:
	float sizeY = 1.f;
	float sizeX = 1.f;
public: 
	sf::Sprite spriteBck;
	sf::Texture textureBck;
	sf::Sprite spriteFront;
	sf::Texture textureFront;
	HealthBarre(std::string imageNamebck, std::string imageNameFront);
	void SetHealthBarre(int life, int lifeMax);
};


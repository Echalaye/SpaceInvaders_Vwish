#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
class Player
{
private:
	float speed = 5.f;
	float sizeY = 3.f;
	float sizeX = 3.f;
	int life = 10;
	int maxLife = 10;

public:
	Player();
	sf::Sprite sprite;
	sf::Texture texture;
	float GetMovementDirection(int valKey, sf::Sprite playerSprite, int screenSizeX);
	void SetLife(int newLife);
	int GetLife();
	int GetMaxLife();
};


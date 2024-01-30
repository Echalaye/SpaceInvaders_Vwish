#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Missile
{
private:
	int degat = 1;
	float speed = 10.f;
	float sizeY = 2.f;
	float sizeX = 2.f;
public:
	Missile();
	sf::Sprite sprite;
	sf::Texture texture;
	void SetDegat(int newDegat);
	int getDamage();
	float GetSpeed();
};


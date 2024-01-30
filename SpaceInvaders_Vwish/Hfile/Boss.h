#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Boss
{

private:
	float speed = 15.f;
	float sizeY = 4.f;
	float sizeX = 4.f;
	int life = 10;
	int maxLife = 10;

public:
	Boss();
	sf::Sprite sprite;
	sf::Texture texture;
	void SetLife(int newLife);
	int GetLife();
	int GetMaxLife();
	float GetSpeed();
	void SetSpeed(float newSpeed);
	
};


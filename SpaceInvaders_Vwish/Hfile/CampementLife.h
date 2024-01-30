#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class CampementLife
{
private:
	float sizeY = 2.f;
	float sizeX = 2.f;
	int life = 9;
public:
	CampementLife();
	sf::Sprite sprite;
	sf::Texture texture;
	void SetDegatRecieveTexture();
	void SetLife(int damage);
	int GetLife();
};



#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Monster
{
private:
	int life = 1;
	float speed = 5.f;
	float sizeY = 2.f;
	float sizeX = 2.f; 
	float speedBoost = 0.2f;
public:
	Monster(std::string imageToLoad);
	sf::Sprite sprite;
	sf::Texture texture;
	float getSpeed();
	void setSpeed(float newSpeed);
	void setLife(int damage);
	int getLife();
	float GetSpeedBoost();
};


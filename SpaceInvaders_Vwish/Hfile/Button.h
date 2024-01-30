#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
	
private:
	float sizeY = 1.f;
	float sizeX = 1.f;
	bool isActive;
	std::string tagButton = "";
public:
	Button(std::string imageName);
	bool GetIsActive();
	void SetIsActive(bool val);
	sf::Sprite sprite;
	sf::Texture texture;
	bool CheckButton(sf::Event::MouseButtonEvent& mouseEvent);
};

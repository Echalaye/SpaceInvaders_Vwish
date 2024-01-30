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

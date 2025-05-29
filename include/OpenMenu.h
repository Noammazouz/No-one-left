#pragma once

#include "Menu.h"

class OpenMenu : public Menu
{
public:
	OpenMenu(sf::RenderWindow& window, const sf::Font& font, const sf::Texture& texture);

	virtual void draw() override;
	virtual void update(sf::Time deltaTime) override;
	virtual void handleInput() override;
};
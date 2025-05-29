#pragma once

#include "Menu.h"

class HelpMenu : public Menu
{
public:
	HelpMenu(sf::RenderWindow& window, const sf::Font& font, const sf::Texture& texture);

	virtual void draw() override;
	virtual void update(sf::Time deltaTime) override;
	virtual void handleInput() override;
};
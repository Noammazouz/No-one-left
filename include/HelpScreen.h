#pragma once

//-----include section-----
#include "Screen.h"

//-----class section-----
class HelpScreen : public Screen
{
public:
	HelpScreen(sf::RenderWindow& window, const sf::Font& font, const sf::Texture& texture);

	virtual void draw() override;
	virtual void update(sf::Time deltaTime) override;
	virtual void handleInput() override;
};
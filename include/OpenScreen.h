#pragma once

//-----include section-----
#include "Screen.h"

//-----class section-----
class OpenScreen : public Screen
{
public:
	OpenScreen(sf::RenderWindow& window, const sf::Font& font, const sf::Texture& texture);

	virtual void draw() override;
	virtual void update(sf::Time deltaTime) override;
	virtual void handleInput() override;
};
#pragma once

//-----include section-----
#include "Screen.h"

//-----class section-----
class HelpScreen : public Screen
{
public:
	HelpScreen();
	~HelpScreen() = default;

	void draw(sf::RenderWindow& window) override;
	void activate(sf::Clock& clockin, int& m_currrentScreen) override;
	void initButtons() override;
	void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window, int& screenState) override;
};
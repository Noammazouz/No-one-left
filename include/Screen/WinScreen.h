#pragma once

//-----include section-----
#include "Screen.h"

//-----class section-----
class WinScreen : public Screen
{
public:
	WinScreen();
	~WinScreen() = default;

	virtual void draw(sf::RenderWindow& window) override;
	virtual void activate(sf::Clock& clocking, int& m_currentScreen) override;

protected:
	virtual void handleMouseClick(const sf::Vector2f& clickPos, int& screenState) override;
	virtual void initButtons() override;
};
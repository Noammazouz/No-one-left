#pragma once
#include "Screen.h"

class WinScreen : public Screen
{
public:
	WinScreen();
	virtual void draw(sf::RenderWindow& window) override;
	virtual void activate(sf::Clock& clockin, int& m_currrentScreen) override;
protected:
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window, int& screenState) override;
	virtual void initButtons() override;
};
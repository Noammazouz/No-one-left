#pragma once

//-----includes section-----
#include "Screen.h"

//-----class section-----
class StartScreen : public Screen
{
public:
	StartScreen();
	~StartScreen() = default;

    void draw(sf::RenderWindow& window) override;
	void activate(sf::Clock& clocking, int& m_currentScreen) override;
	void initButtons() override;
	void handleMouseClick(const sf::Vector2f& clickPos, int& screenState) override;

private:
};
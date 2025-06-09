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
	void activate(sf::Clock& clockin, int& m_currrentScreen) override;
	void initButtons() override;
	void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window, int& screenState) override;

private:
};
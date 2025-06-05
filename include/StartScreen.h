#pragma once

//-----includes section-----
#include "Screen.h"

//-----class section-----
class StartScreen : public Screen
{
public:
	StartScreen() = default;
	~StartScreen() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void activate(sf::Clock& clockin, int& m_currrentScreen) = 0;
	virtual void run(sf::RenderWindow& window, int& m_currrentScreen);

private:
};
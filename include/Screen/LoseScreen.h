#pragma once 

//-----include section-----
#include "Screen.h"

//-----class section-----
class LoseScreen : public Screen 
{
public:
	LoseScreen();
	~LoseScreen() = default;

	virtual void draw(sf::RenderWindow& window) override;
	virtual void activate(sf::Clock& clockin, int& m_currrentScreen) override;

protected:
	virtual void handleMouseClick(const sf::Vector2f& clickPos, int& screenState) override;
	virtual void initButtons() override;
};
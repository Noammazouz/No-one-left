#pragma once
#include "Screen.h"

class MenuScreen : public Screen
{
public:
	MenuScreen() = default;
	~MenuScreen() = default;
	virtual void activate(sf::RenderWindow& window);
private:
};
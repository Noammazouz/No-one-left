#pragma once

//-----includes section-----
#include "Screen.h"

//-----class section-----
class MenuScreen : public Screen
{
public:
	MenuScreen() = default;
	~MenuScreen() = default;
	virtual void activate(sf::RenderWindow& window);

private:
};
#pragma once 

//-----include section-----
#include <vector>
#include <SFML/Graphics.hpp>
#include "Const.h"
#include "Button.h"
#include "MusicManager.h"

//-----class section-----
class Screen
{
public:
	Screen();
	virtual ~Screen() = default;

	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void activate(sf::Clock& clocking, int& m_currentScreen) = 0;
	virtual void run(sf::RenderWindow& window, int& m_currentScreen);
	void setPreviousScreen(int previousScreen);

protected:
	virtual void handleMouseClick(const sf::Vector2f& clickPos, int& screenState) = 0;
	virtual void initButtons() = 0;
	virtual void drawButtons(sf::RenderWindow& window);
	void handleMuting();
	void handleKeyPressed(sf::Event::KeyEvent event, int& currentScreen);

	int m_previousScreen;
	std::vector<Button> m_buttons;
};
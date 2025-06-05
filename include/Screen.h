#pragma once 

//-----include section-----
#include <vector>
#include <SFML/Graphics.hpp>
#include "Const.h"
#include "Button.h"
#include "ResourcesManager.h"

//-----class section-----
class Screen
{
public:
	Screen() = default;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void activate(sf::Clock& clockin, int& m_currrentScreen) = 0;
	virtual void run(sf::RenderWindow& window, int& m_currrentScreen);

protected:
	virtual void handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window) = 0;
	virtual void initButtons(GameState buttonAmmout) = 0;
	void handleMuting(int currrentScreen);
	void handleKeyPressed(sf::Event::KeyEvent event, int& currrentScreen, sf::RenderWindow& window);
	void handleMusicTransition(bool toGameplay);

	bool m_inGameplay = false;
	std::vector<Button> m_buttons;

};
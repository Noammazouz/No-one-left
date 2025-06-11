//-----includes section-----
#include "HelpScreen.h"

//-----functions section------
//-----------------------------------------------------------------------------
HelpScreen::HelpScreen()
{
	// Initialize buttons
	initButtons();
}

//-----------------------------------------------------------------------------
void HelpScreen::draw(sf::RenderWindow& window)
{
	/*sf::Texture texture = ResourcesManager::getInstance().getTexture("help menu");
	texture.setSmooth(true);

	sf::Sprite helpMenu(texture);
	window.draw(helpMenu);*/
	//drawButtons(window);
	//m_buttons[0].draw(window);
}

//-----------------------------------------------------------------------------
void HelpScreen::activate(sf::Clock& clockin, int& m_currrentScreen)
{}

//-----------------------------------------------------------------------------
void HelpScreen::initButtons()
{}

//-----------------------------------------------------------------------------
void  HelpScreen::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window, int& screenState)
{}
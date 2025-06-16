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
	window.setView(window.getDefaultView());
	sf::Texture texture = ResourcesManager::getInstance().getTexture("help screen");
	texture.setSmooth(true);

	sf::Sprite helpMenu(texture);
	helpMenu.setScale(1.8f, 1.75f); // Scale the help menu to fit the window
	window.draw(helpMenu);
	drawButtons(window);
	//m_buttons[0].draw(window);
}

//-----------------------------------------------------------------------------
void HelpScreen::activate(sf::Clock& clockin, int& m_currrentScreen)
{}

//-----------------------------------------------------------------------------
void HelpScreen::initButtons()
{
	// Initialize buttons for the help screen
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2f position(20.f, 20.f);
	m_buttons.emplace_back(RETURN_BUTTON, position);
}

//-----------------------------------------------------------------------------
void  HelpScreen::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window, int& screenState)
{
	for (int index = 0; index < m_buttons.size(); ++index)
	{
		if (m_buttons[index].getBounds().contains(clickPos))
		{
			screenState = m_previousScreen;
			std::cout << "Returning to previous screen: " << m_previousScreen << std::endl;
		}
	}
}

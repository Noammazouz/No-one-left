//-----includes section-----
#include "HelpScreen.h"

//-----functions section------
//-----------------------------------------------------------------------------
HelpScreen::HelpScreen()
{
	initButtons();
}

//-----------------------------------------------------------------------------
void HelpScreen::draw(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());
	sf::Texture texture = ResourcesManager::getInstance().getTexture("help screen");
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Sprite helpMenu(texture);
	helpMenu.setScale(desktop.width * WINDOW_RATIO / texture.getSize().x,
					  desktop.height * WINDOW_RATIO / texture.getSize().y); // Scale the background to fit the window
	window.draw(helpMenu);
	drawButtons(window);
	auto helpText = ResourcesManager::getInstance().getHelpText();
	for(const auto& text : helpText)
	{
		window.draw(text);
	}
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
	sf::Vector2f position(40.f, 40.f);
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
		}
	}
}

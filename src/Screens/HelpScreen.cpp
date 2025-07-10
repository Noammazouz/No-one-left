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
	sf::Texture texture = ResourcesManager::getInstance().getTexture(HELP_SCREEN_BACKGROUND);
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Sprite helpMenu(texture);
	helpMenu.setScale(desktop.width * WINDOW_RATIO / texture.getSize().x,
					  desktop.height * WINDOW_RATIO / texture.getSize().y); //Scale the background to fit the window
	window.draw(helpMenu);
	drawButtons(window);
	auto helpText = ResourcesManager::getInstance().getHelpText();
	for(const auto& text : helpText)
	{
		window.draw(text);
	}
}

//-----------------------------------------------------------------------------
void HelpScreen::activate(sf::Clock& /*clocking*/, int& /*m_currentScreen*/)
{
	// Ensure menu music is playing
	auto& musicManager = MusicManager::getInstance();
	if (musicManager.getCurrentMusicType() != MusicManager::MusicType::MENU)
	{
		musicManager.setCurrentMusic(MusicManager::MusicType::MENU);
	}
}

//-----------------------------------------------------------------------------
void HelpScreen::initButtons()
{
	// Initialize buttons for the help screen
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2f position(40.f, 40.f);
	m_buttons.emplace_back(RETURN_BUTTON, position);
}

//-----------------------------------------------------------------------------
void  HelpScreen::handleMouseClick(const sf::Vector2f& clickPos, int& screenState)
{
	for (int index = 0; index < m_buttons.size(); ++index)
	{
		if (m_buttons[index].getBounds().contains(clickPos))
		{
			screenState = m_previousScreen;
		}
	}
}

//-----includes section-----
#include "StartScreen.h"

//-----functions section------
//-----------------------------------------------------------------------------
StartScreen::StartScreen()
{
	initButtons();
}

//-----------------------------------------------------------------------------
void StartScreen::draw(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());
	sf::Texture backgroundTexture = ResourcesManager::getInstance().getTexture(START_SCREEN_BACKGROUND);
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setScale(desktop.width * WINDOW_RATIO / backgroundTexture.getSize().x, 
							  desktop.height * WINDOW_RATIO / backgroundTexture.getSize().y); // Scale the background to fit the window
	window.draw(backgroundSprite);
	drawButtons(window);
}

//-----------------------------------------------------------------------------
void StartScreen::activate(sf::Clock& /*clocking*/, int& /*m_currentScreen*/)
{
	// Menu music should already be playing - just ensure it's correct
	ensureCorrectMusicPlaying();
}

//-----------------------------------------------------------------------------
void StartScreen::initButtons()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	std::vector<std::string> buttonNames = { START_NEW_GAME_BUTTON, HELP_MENU_BUTTON, EXIT_BUTTON};
	for (int index = 0; index < buttonNames.size(); ++index)
	{
		sf::Vector2f position(static_cast<float>(desktop.width * WINDOW_RATIO / 2), static_cast<float>(desktop.height * WINDOW_RATIO / 5 + 300 * index));
		m_buttons.emplace_back(buttonNames[index], position);
	}
}

//-----------------------------------------------------------------------------
void StartScreen::handleMouseClick(const sf::Vector2f& clickPos, int& screenState)
{
	for (int index = 0; index < m_buttons.size(); ++index)
	{
		if(m_buttons[index].getBounds().contains(clickPos))
		{
			switch (index)
			{
				case START_GAME:
				{
					screenState = GAME_SCREEN;
					return;
				}
				case HELP:
				{
					screenState = HELP_SCREEN;
					break;
				}
				case EXIT:
				{
					exit(EXIT_SUCCESS);
					break;
				}
			}
		}
	}
}
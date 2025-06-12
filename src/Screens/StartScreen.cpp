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
	sf::Texture backgroundTexture = ResourcesManager::getInstance().getTexture("startScreen");
	backgroundTexture.setSmooth(true);
	sf::Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setScale(1.5f, 1.5f); // Scale the background to fit the window
	window.draw(backgroundSprite);
	drawButtons(window);
}

//-----------------------------------------------------------------------------
void StartScreen::activate(sf::Clock& clockin, int& m_currrentScreen)
{
}

//-----------------------------------------------------------------------------
void StartScreen::initButtons()
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	std::vector<std::string> buttonNames = { "start game", "help", "exit"};
	for (int index = 0; index < buttonNames.size(); ++index)
	{
		sf::Vector2f position(static_cast<float>(desktop.width * WINDOW_RATIO / 2), static_cast<float>(desktop.height * WINDOW_RATIO / 5 + 300 * index));
		m_buttons.emplace_back(buttonNames[index], position);
	}
}

//-----------------------------------------------------------------------------
void StartScreen::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window, int& screenState)
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
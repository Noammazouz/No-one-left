#include "StartScreen.h"

StartScreen::StartScreen()
{
	initButtons();
}

void StartScreen::draw(sf::RenderWindow& window)
{
	// Draw the background
	sf::Texture backgroundTexture = ResourcesManager::getInstance().getTexture("startScreen");
	backgroundTexture.setSmooth(true);
	sf::Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setScale(1.5f, 1.5f); // Scale the background to fit the window
	window.draw(backgroundSprite);
	// Draw buttons
	for (auto& button : m_buttons)
	{
		button.draw(window);
	}
	// Display the contents of the window
	//window.display();
}

void StartScreen::activate(sf::Clock& clockin, int& m_currrentScreen)
{

}

void StartScreen::initButtons()
{
	std::vector<std::string> buttonNames = { "start game", "help", "exit"};
	for (int index = 0; index < buttonNames.size(); ++index)
	{
		sf::Vector2f position(static_cast<float>(WINDOW_WIDTH / 2), static_cast<float>(WINDOW_HEIGHT / 5 + 300 * index));
		Button button(buttonNames[index], index, position);
		m_buttons.push_back(button);
	}
}

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
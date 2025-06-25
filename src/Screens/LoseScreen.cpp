//-----include section-----
#include "LoseScreen.h"

// LoseScreen.cpp
//-----functions section------
//-----------------------------------------------------------------------------
LoseScreen::LoseScreen()
{
    initButtons();
}

//-----------------------------------------------------------------------------
void LoseScreen::draw(sf::RenderWindow& window) 
{
	window.setView(window.getDefaultView());
	sf::Texture texture = ResourcesManager::getInstance().getTexture(LOSE_SCREEN_BACKGROUND);
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Sprite loseScreen(texture);
	loseScreen.setScale(desktop.width * WINDOW_RATIO / texture.getSize().x,
		desktop.height * WINDOW_RATIO / texture.getSize().y); // Scale the background to fit the window
	window.draw(loseScreen);
	drawButtons(window);
}

//-----------------------------------------------------------------------------
void LoseScreen::activate(sf::Clock& /*clock*/, int& /*state*/) 
{
	// Ensure menu music is playing
	if (getCurrentMusicState() != MusicState::MENU)
	{
		setMusicState(MusicState::MENU);
	}
}

//-----------------------------------------------------------------------------
void LoseScreen::handleMouseClick(const sf::Vector2f& clickPos, int& screenState)
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
				case HOME:
				{
					screenState = START_SCREEN;
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

//-----------------------------------------------------------------------------
void LoseScreen::initButtons() 
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	std::vector<std::string> buttonNames = { START_NEW_GAME_BUTTON, START_MENU_BUTTON , EXIT_BUTTON };
	for (int index = 0; index < buttonNames.size(); ++index)
	{
		sf::Vector2f position(static_cast<float>(desktop.width * WINDOW_RATIO / 2),
			static_cast<float>(desktop.height * WINDOW_RATIO / 5 + 300 * index));
		m_buttons.emplace_back(buttonNames[index], position);
	}
}

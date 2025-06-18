//-----include section-----
#include "Screen.h"

//-----functions section------
//-----------------------------------------------------------------------------
Screen::Screen()
{}

//-----------------------------------------------------------------------------
void Screen::run(sf::RenderWindow& window, int& currentScreen)
{

	for (auto event = sf::Event{}; window.pollEvent(event);)
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			case sf::Event::MouseButtonReleased:
			{
				handleMouseClick(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }), window, currentScreen);
				break;
			}
			case sf::Event::KeyPressed:
			{
				handleKeyPressed(event.key, currentScreen, window);
				break;
			}
		}
	}
}

//-----------------------------------------------------------------------------
void Screen::setPreviousScreen(int previousScreen)
{
	m_previousScreen = previousScreen;
}

//-----------------------------------------------------------------------------
void Screen::handleKeyPressed(sf::Event::KeyEvent event, int& currentScreen, sf::RenderWindow& window)
{
	if (event.code == sf::Keyboard::Escape)
	{
		currentScreen = int(START_SCREEN);
		handleMusicTransition(false);
		return;
	}
	
	if (event.code == sf::Keyboard::M)
	{
		handleMuting(currentScreen);
	}
}

//-----------------------------------------------------------------------------
void Screen::handleMusicTransition(bool toGameplay)
{
	if (toGameplay && !m_inGameplay)
	{
		ResourcesManager::getInstance().getMusic(MENU_MUSIC).stop();
		if (ResourcesManager::getInstance().getMusic(GAME_MUSIC).getStatus() != sf::Music::Playing)
		{
			ResourcesManager::getInstance().getMusic(GAME_MUSIC).play();
		}
		m_inGameplay = true;
	}
	else if (!toGameplay && m_inGameplay)
	{
		ResourcesManager::getInstance().getMusic(GAME_MUSIC).stop();
		ResourcesManager::getInstance().getMusic(MENU_MUSIC).play();
		m_inGameplay = false;
	}
	else
	{
		ResourcesManager::getInstance().getMusic(MENU_MUSIC).play();
	}
}

//-----------------------------------------------------------------------------
void Screen::handleMuting(int currentScreen)
{
	std::string musicStatus;
	if(currentScreen == int(GAME_SCREEN))
	{
		musicStatus = GAME_MUSIC;
	}
	else
	{
		musicStatus = MENU_MUSIC;
	}

	if (ResourcesManager::getInstance().getMusic(musicStatus).getStatus() == sf::Music::Playing)
	{
		ResourcesManager::getInstance().getMusic(musicStatus).pause();
	}
	else
	{
		ResourcesManager::getInstance().getMusic(musicStatus).play();
	}
}

//-----------------------------------------------------------------------------
void Screen::drawButtons(sf::RenderWindow& window)
{
	for (auto& button : m_buttons)
	{
		button.draw(window);
	}
}
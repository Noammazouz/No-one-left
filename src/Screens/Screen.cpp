//-----include section-----
#include "Screen.h"
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
Screen::Screen()
	: m_previousScreen(START_SCREEN)
{
	// Initialize music manager on first screen creation
	static bool musicInitialized = false;
	if (!musicInitialized)
	{
		if (MusicManager::getInstance().initialize())
		{
			// Start menu music immediately
			MusicManager::getInstance().setCurrentMusic(MusicManager::MusicType::MENU);
			musicInitialized = true;
		}
		else
		{
			std::cerr << "[Screen] Failed to initialize music system!" << std::endl;
		}
	}
}

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
				handleMouseClick(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }), currentScreen);
				break;
			}
			case sf::Event::KeyPressed:
			{
				handleKeyPressed(event.key, currentScreen);
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
void Screen::handleKeyPressed(sf::Event::KeyEvent event, int& currentScreen)
{
	if (event.code == sf::Keyboard::Escape)
	{
		currentScreen = int(START_SCREEN);
		MusicManager::getInstance().setCurrentMusic(MusicManager::MusicType::MENU);
		return;
	}
	
	if (event.code == sf::Keyboard::M)
	{
		handleMuting();
	}
}



//-----------------------------------------------------------------------------
void Screen::handleMuting()
{
	auto& musicManager = MusicManager::getInstance();
	if (!musicManager.isMuted())
	{
		musicManager.muteMusic();
	}
	else
	{
		musicManager.unmuteMusic();
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


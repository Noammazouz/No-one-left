//-----include section-----
#include "Screen.h"
#include <iostream>

//-----functions section------

//-----------------------------------------------------------------------------
// Static member initialization
Screen::MusicState Screen::s_currentMusicState = Screen::MusicState::MENU;
bool Screen::s_musicMuted = false;

//-----------------------------------------------------------------------------
Screen::Screen()
	: m_previousScreen(START_SCREEN)
{
	// Initialize music to menu state if this is the first screen
	setMusicState(MusicState::MENU);
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
		setMusicState(MusicState::MENU);
		return;
	}
	
	if (event.code == sf::Keyboard::M)
	{
		handleMuting(currentScreen);
	}
}



//-----------------------------------------------------------------------------
void Screen::handleMuting(int currentScreen)
{
	if (!s_musicMuted)
	{
		// Mute music
		ResourcesManager::getInstance().getMusic(MENU_MUSIC).stop();
		ResourcesManager::getInstance().getMusic(GAME_MUSIC).stop();
		s_musicMuted = true;
	}
	else
	{
		// Unmute music - restore previous state
		s_musicMuted = false;
		ensureCorrectMusicPlaying();
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

//-----------------------------------------------------------------------------
void Screen::setMusicState(MusicState newState)
{
	if (s_musicMuted) return; // Don't change music if muted
	
	if (s_currentMusicState == newState) 
	{
		// State is correct, but make sure music is actually playing
		ensureCorrectMusicPlaying();
		return;
	}
	
	// Stop all music first
	ResourcesManager::getInstance().getMusic(MENU_MUSIC).stop();
	ResourcesManager::getInstance().getMusic(GAME_MUSIC).stop();
	
	// Start appropriate music
	switch (newState)
	{
		case MusicState::MENU:
			ResourcesManager::getInstance().getMusic(MENU_MUSIC).play();
			break;
			
		case MusicState::GAME:
			ResourcesManager::getInstance().getMusic(GAME_MUSIC).play();
			break;
	}
	
	s_currentMusicState = newState;
}

//-----------------------------------------------------------------------------
Screen::MusicState Screen::getCurrentMusicState()
{
	return s_currentMusicState;
}

//-----------------------------------------------------------------------------
void Screen::ensureCorrectMusicPlaying()
{
	if (s_musicMuted) return;
	
	bool menuShouldPlay = (s_currentMusicState == MusicState::MENU);
	bool gameShouldPlay = (s_currentMusicState == MusicState::GAME);
	
	bool menuIsPlaying = (ResourcesManager::getInstance().getMusic(MENU_MUSIC).getStatus() == sf::Music::Playing);
	bool gameIsPlaying = (ResourcesManager::getInstance().getMusic(GAME_MUSIC).getStatus() == sf::Music::Playing);
	
	// Fix any discrepancies
	if (menuShouldPlay && !menuIsPlaying)
	{
		ResourcesManager::getInstance().getMusic(GAME_MUSIC).stop();
		ResourcesManager::getInstance().getMusic(MENU_MUSIC).play();
	}
	else if (gameShouldPlay && !gameIsPlaying)
	{
		ResourcesManager::getInstance().getMusic(MENU_MUSIC).stop();
		ResourcesManager::getInstance().getMusic(GAME_MUSIC).play();
	}
	else if (!menuShouldPlay && menuIsPlaying)
	{
		ResourcesManager::getInstance().getMusic(MENU_MUSIC).stop();
	}
	else if (!gameShouldPlay && gameIsPlaying)
	{
		ResourcesManager::getInstance().getMusic(GAME_MUSIC).stop();
	}
}
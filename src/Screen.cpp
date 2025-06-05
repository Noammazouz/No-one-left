#include "Screen.h"


void Screen::run(sf::RenderWindow& window, int& currrentScreen)
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
			handleMouseClick(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }), window);
			break;
		}
		case sf::Event::KeyPressed:
		{
			handleKeyPressed(event.key, currrentScreen, window);
			break;
		}
		}
	}
}

//---------------------------------
void Screen::handleKeyPressed(sf::Event::KeyEvent event, int& currrentScreen, sf::RenderWindow& window)
{
	if (event.code == sf::Keyboard::Escape)
	{
		window.close();
		currrentScreen = int(START_SCREEN);
		return;
	}
	
	if (event.code == sf::Keyboard::M)
	{
		handleMuting(currrentScreen);
	}
}

//void Screen::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
//{
//	for(auto& button : m_buttons)
//	{
//		if (button.getGlobalBounds().contains(clickPos))
//		{
//			button.onClick(window);
//			return;
//		}
//	}
//}

//-----------------------------
void Screen::handleMusicTransition(bool toGameplay)
{
	if (toGameplay && !m_inGameplay)
	{
		ResourcesManager::getInstance().getMusic("menu").stop();
		if (ResourcesManager::getInstance().getMusic("game").getStatus() != sf::Music::Playing)
		{
			ResourcesManager::getInstance().getMusic("game").play();
		}
		m_inGameplay = true;
	}
	else if (!toGameplay && m_inGameplay)
	{
		ResourcesManager::getInstance().getMusic("game").stop();
		ResourcesManager::getInstance().getMusic("menu").play();
		m_inGameplay = false;
	}
	else
	{
		ResourcesManager::getInstance().getMusic("menu").play();
	}
}

//-------------------------------------
void Screen::handleMuting(int currrentScreen)
{
	std::string musicStatus;
	if(currrentScreen == int(GAME_SCREEN))
	{
		musicStatus = "game";
	}
	else
	{
		musicStatus = "menu";
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


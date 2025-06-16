//-----include section-----
#include "Controller.h"

//-----functions section------
//-----------------------------------------------------------------------------
Controller::Controller()
	: m_currentScreen(int(START_SCREEN))
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	m_window.create(sf::VideoMode(desktop.width * WINDOW_RATIO, desktop.height * WINDOW_RATIO), "No One Left");
	initScreen();
}

//----------------------------------------------------------------------------
void Controller::run()
{
	sf::Clock clock;
	while (m_window.isOpen())
	{
		//clock.restart();
		m_window.clear();
		m_screens[m_currentScreen]->draw(m_window);
		m_window.display();
		m_screens[m_currentScreen]->activate(clock, m_currentScreen);
		m_screens[m_currentScreen]->run(m_window, m_currentScreen);
		if (m_currentScreen  != HELP_SCREEN)
		m_screens[HELP_SCREEN]->setPreviousScreen(m_currentScreen);
	}
}

//----------------------------------------------------------------------------
void Controller::initScreen()
{
    m_screens.push_back(std::make_unique<StartScreen>());
	m_screens.push_back(std::make_unique<HelpScreen>());
	m_screens.push_back(std::make_unique<GameScreen>());
	m_screens.push_back(std::make_unique<WinScreen>());
	m_screens.push_back(std::make_unique<LoseScreen>());
}

#include "WinScreen.h"

WinScreen::WinScreen()
{
	initButtons();
}

//--------------------------------------------------------------
void WinScreen::draw(sf::RenderWindow& window)
{

}

//--------------------------------------------------------------
void WinScreen::activate(sf::Clock& /*clockin*/, int& /*m_currrentScreen*/)
{
	handleMusicTransition(false); // Start menu music
}

//--------------------------------------------------------------
void WinScreen::handleMouseClick(const sf::Vector2f& clickPos, int& screenState)
{

}

//--------------------------------------------------------------
void WinScreen::initButtons()
{

}
//-----include section-----
#include "Button.h"

//-----functions section------
//-----------------------------------------------------------------------------
Button::Button(std::string buttonName, sf::Vector2f pos) : m_buttonType(buttonName)
{
	setSprite(pos);  //Initialize size when button is created
}

////-----------------------------------------------------------------------------
//sf::Vector2f Button::getPosition() const
//{
//	return m_position;
//}
//
////-----------------------------------------------------------------------------
//void Button::setPosition(int place)
//{
//	//m_position.x = 30.f;
//	m_position.x = (WINDOW_WIDTH - BUTTON_WIDTH) / 2;
//
//	//calculate vertical starting position for centering
//	float totalButtonsHeight = START_WINDOW_BUTTONS_NUM * BUTTON_HEIGHT +
//		(START_WINDOW_BUTTONS_NUM - 1) * BUTTON_SPACING;
//	float startingY = (WINDOW_HEIGHT - totalButtonsHeight) / 2;
//
//	//vertical position for each button
//	m_position.y = startingY + (BUTTON_HEIGHT + BUTTON_SPACING) * place;
//}
//
////-----------------------------------------------------------------------------
//sf::Vector2f Button::getSize() const
//{
//	return m_size;
//}

//-----------------------------------------------------------------------------
void Button::setSprite(sf::Vector2f pos)
{
	m_buttonSprite.setTexture(ResourcesManager::getInstance().getTexture(m_buttonType));
	m_buttonSprite.setOrigin(static_cast<float>(m_buttonSprite.getTexture()->getSize().x) / 2.0f, static_cast<float>(m_buttonSprite.getTexture()->getSize().y) / 2.0f);
	m_buttonSprite.setPosition(pos);
	m_buttonSprite.setScale(static_cast<float>(0.3), static_cast<float>(0.3));
}

////-----------------------------------------------------------------------------
//sf::RectangleShape Button::makeButtonRectangle() const
//{
//	sf::RectangleShape buttonRectangle(sf::Vector2f(3, 3));
//
//	buttonRectangle.setPosition(m_buttonSprite.getPosition());
//
//	buttonRectangle.setFillColor(sf::Color(0, 0, 0, 0));
//	buttonRectangle.setTexture(NULL);
//
//	return buttonRectangle;
//}

//-----------------------------------------------------------------------------
//This function draw each button.
void Button::draw(sf::RenderWindow& window)
{
	window.draw(m_buttonSprite);

}

////-----------------------------------------------------------------------------
//const std::string Button::getButtonType() const
//{
//	return m_buttonType;
//}

sf::FloatRect Button::getBounds() const
{
	return m_buttonSprite.getGlobalBounds();
}
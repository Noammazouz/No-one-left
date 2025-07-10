//-----include section-----
#include "Button.h"

//-----functions section------
//-----------------------------------------------------------------------------
Button::Button(std::string buttonName, sf::Vector2f pos) : m_buttonType(buttonName)
{
	setSprite(pos); //Initialize size when button is created
}

//-----------------------------------------------------------------------------
void Button::setSprite(sf::Vector2f pos)
{
	m_buttonSprite.setTexture(ResourcesManager::getInstance().getTexture(m_buttonType));
	m_buttonSprite.setOrigin(static_cast<float>(m_buttonSprite.getTexture()->getSize().x) / 2.0f, static_cast<float>(m_buttonSprite.getTexture()->getSize().y) / 2.0f);
	m_buttonSprite.setPosition(pos);
	m_buttonSprite.setScale(static_cast<float>(0.3), static_cast<float>(0.3));
}

//-----------------------------------------------------------------------------
//This function draw each button.
void Button::draw(sf::RenderWindow& window)
{
	window.draw(m_buttonSprite);

}

//-----------------------------------------------------------------------------
sf::FloatRect Button::getBounds() const
{
	return m_buttonSprite.getGlobalBounds();
}
//-----include section-----
#include "GameObject.h"
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
GameObject::GameObject()
{}

//-----------------------------------------------------------------------------
GameObject::GameObject(std::string name, const sf::Vector2f& position)
{
	auto& texture = ResourcesManager::getInstance().getTexture(name);
    m_pic.setTexture(texture);
	m_pic.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2); //Set origin to center.
    m_pic.setPosition(position);
}

//-----------------------------------------------------------------------------
sf::FloatRect GameObject::getBounds() const
{
    return m_pic.getGlobalBounds();
}

//-----------------------------------------------------------------------------
void GameObject::draw(sf::RenderWindow& window)
{
    window.draw(m_pic);
}

//-----------------------------------------------------------------------------
void GameObject::setPosition(const sf::Vector2f& position)
{
	m_pic.setPosition(position);
}

//-----------------------------------------------------------------------------
sf::Vector2f GameObject::getPosition() const
{
	return m_pic.getPosition();
}

//-----------------------------------------------------------------------------
bool GameObject::isDead() const
{
    return m_isDead;
}

//-----------------------------------------------------------------------------
void GameObject::setLife(const bool life)
{
	m_isDead = life;
}
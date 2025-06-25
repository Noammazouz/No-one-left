//-----include section-----
#include "Weapons.h"

//-----functions section------
//-----------------------------------------------------------------------------
Weapons::Weapons(const std::string& name, const sf::Vector2f& position)
	: ItemsToCollect(name, position), m_weaponType(name)
{
	auto& texture = ResourcesManager::getInstance().getTexture(name);
	m_pic.setTexture(texture);
	m_pic.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2); //Set origin to center.
	m_pic.setPosition(position);
}
//-----include section-----
#include "WeaponsGift.h"

//-----functions section------
//-----------------------------------------------------------------------------
WeaponsGift::WeaponsGift(const std::string& name, const sf::Vector2f& position)
	: ItemsToCollect(name, position), m_weaponType(name)
{}

//-----------------------------------------------------------------------------
const std::string& WeaponsGift::getWeaponType() const
{
	return m_weaponType;
}
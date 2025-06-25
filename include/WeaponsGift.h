#pragma once

//-----include section-----
#include "ItemsToCollect.h"

//-----class section-----
class WeaponsGift : public ItemsToCollect
{
public:
	WeaponsGift(const std::string& name, const sf::Vector2f& position);
	~WeaponsGift() = default;

	virtual const std::string& getWeaponType() const;

private:
	std::string m_weaponType; //Type of weapon (e.g., "rifle", "machine gun", "bazooka").
};
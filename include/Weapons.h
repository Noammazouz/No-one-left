#pragma once

//-----include section-----
#include "ItemsToCollect.h"

//-----class section-----
class Weapons : public ItemsToCollect
{
public:
	Weapons(const std::string& name, const sf::Vector2f& position);
	~Weapons() = default;

private:
	std::string m_weaponType; //Type of weapon (e.g., "rifle", "machine gun", "bazooka").
};
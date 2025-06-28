#pragma once

//-----include section-----
#include "WeaponsGift.h"
#include <SFML/Graphics.hpp>

//-----class section-----
class MachineGunGift : public WeaponsGift
{
public:
	MachineGunGift(const std::string& name, const sf::Vector2f& position);
	~MachineGunGift() = default;
};
#pragma once

//-----include section-----
#include "WeaponsGift.h"
#include <SFML/Graphics.hpp>

//-----class section-----
class RifleGift : public WeaponsGift
{
public:
	RifleGift(const std::string& name, const sf::Vector2f& position);
	~RifleGift() = default;
};
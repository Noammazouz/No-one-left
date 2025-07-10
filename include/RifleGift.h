#pragma once

//-----include section-----
#include <SFML/Graphics.hpp>
#include "WeaponsGift.h"

//-----class section-----
class RifleGift : public WeaponsGift
{
public:
	RifleGift(const std::string& name, const sf::Vector2f& position);
	~RifleGift() = default;
};
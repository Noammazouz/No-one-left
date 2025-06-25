#pragma once

//-----include section-----
#include "WeaponsGift.h"
#include <SFML/Graphics.hpp>

//-----class section-----
class BazookaGift : public WeaponsGift
{
public:
	BazookaGift(const std::string& name, const sf::Vector2f& position);
	~BazookaGift() = default;
};
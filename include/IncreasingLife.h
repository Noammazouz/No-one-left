#pragma once

//-----include section-----
#include <SFML/Graphics.hpp>
#include "ItemsToCollect.h"

//-----class section-----
class IncreasingLife : public ItemsToCollect
{
public:
	IncreasingLife(std::string name, const sf::Vector2f& position);
	~IncreasingLife() = default;
};
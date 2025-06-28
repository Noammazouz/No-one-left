#pragma once

//-----include section-----
#include "ItemsToCollect.h"
#include <SFML/Graphics.hpp>

//-----class section-----
class RemoveTime : public ItemsToCollect
{
public:
	RemoveTime(const std::string& name, const sf::Vector2f& position);
	virtual ~RemoveTime() = default;
};


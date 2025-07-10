#pragma once

//-----include section-----
#include <SFML/Graphics.hpp>
#include "ItemsToCollect.h"

//-----class section-----
class RemoveTime : public ItemsToCollect
{
public:
	RemoveTime(const std::string& name, const sf::Vector2f& position);
	virtual ~RemoveTime() = default;
};


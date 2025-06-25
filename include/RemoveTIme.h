#pragma once

//-----include section-----
#include "ItemsToCollect.h"
#include <SFML/Graphics.hpp>

//-----class section-----
class RemoveTime : public ItemsToCollect
{
public:
	RemoveTime(std::string name, const sf::Vector2f& position);
	~RemoveTime() = default;

};


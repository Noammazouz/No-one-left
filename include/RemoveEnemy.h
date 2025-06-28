#pragma once

//-----include section-----
#include "ItemsToCollect.h"
#include <SFML/Graphics.hpp>

//-----class section-----
class RemoveEnemy : public ItemsToCollect
{
public:
	RemoveEnemy(const std::string& name, const sf::Vector2f& position);
	virtual ~RemoveEnemy() = default;
};
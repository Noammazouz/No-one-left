#pragma once

//-----include section-----
#include <SFML/Graphics.hpp>
#include "ItemsToCollect.h"

//-----class section-----
class RemoveEnemy : public ItemsToCollect
{
public:
	RemoveEnemy(const std::string& name, const sf::Vector2f& position);
	virtual ~RemoveEnemy() = default;
};
#pragma once

#include <SFML/Graphics.hpp>


class MoveBehavior
{
	public:
		MoveBehavior() = default;
		virtual ~MoveBehavior() = default;
		virtual void Move(sf::Vector2f playerLoc = {0 ,0}) = 0;
};
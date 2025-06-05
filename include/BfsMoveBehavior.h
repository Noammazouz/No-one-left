#pragma once

//-----include section-----
#include "MoveBehavior.h"

//-----class section-----
class BfsMoveBehavior : public MoveBehavior
{
public:
	BfsMoveBehavior() = default;
	virtual ~BfsMoveBehavior() = default;

	// Override the move method
	virtual void Move(sf::Vector2f playerLoc) override;
};
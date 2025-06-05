#pragma once

//-----includes section-----
#include "MoveBehavior.h"

//-----class section-----
class RandomMoveBehavior : public MoveBehavior
{
public:
	RandomMoveBehavior() = default;
	virtual ~RandomMoveBehavior() = default;

	// Override the move method
	virtual void Move(sf::Vector2f playerLoc) override;
};
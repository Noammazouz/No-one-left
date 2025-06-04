#pragma once 

#include "MoveBehavior.h"

class AxisMoveBehavior : public MoveBehavior
{
public:
	AxisMoveBehavior() = default;
	virtual ~AxisMoveBehavior() = default;

	// Override the move method
	virtual void Move(sf::Vector2f playerLoc) override;
};
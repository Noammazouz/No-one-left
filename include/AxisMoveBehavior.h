#pragma once 

//-----include section-----
#include "MoveBehavior.h"

//-----class section-----
class AxisMoveBehavior : public MoveBehavior
{
public:
    AxisMoveBehavior() = default;
    virtual ~AxisMoveBehavior() = default;
    virtual void Move(sf::Vector2f playerPos, float deltaTime) override;

private:
    bool isMovingX = true; 
    float Timer = 0;
    const float CHANGE_DIRECTION_TIME = 1.0f;
};

#pragma once

//-----include section-----
#include <SFML/Graphics.hpp>

//-----class section-----
class MoveBehavior
{
public:
    MoveBehavior() = default;
    virtual ~MoveBehavior() = default;
    virtual void Move(sf::Vector2f playerPos, float deltaTime) = 0;

    sf::Vector2f getPosition() const { return enemyPos; }
    void setPosition(sf::Vector2f pos) { enemyPos = pos; }
    void setSpeed(float newSpeed) { speed = newSpeed; }

protected:
    sf::Vector2f enemyPos;
    float speed = 100.0f; 
};
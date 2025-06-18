#pragma once

//-----include section-----
#include <SFML/Graphics.hpp>
//#include <SFML/Graphics.hpp>

//-----class section-----
class MoveBehavior
{
public:
    MoveBehavior() = default;
    virtual ~MoveBehavior() = default;

    virtual sf::Vector2f Move(sf::Vector2f playerPos, sf::Time deltaTime , sf::Vector2f enemyPos) = 0;
};
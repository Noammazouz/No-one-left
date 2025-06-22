#pragma once

//-----include section-----
#include "ItemsToCollect.h"
#include <SFML/Graphics.hpp>

//-----class section-----
class Bullets : public ItemsToCollect
{
public:
    Bullets(std::string name, const sf::Vector2f& position);
    ~Bullets() = default;
};
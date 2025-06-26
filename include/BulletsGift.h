#pragma once

//-----include section-----
#include "ItemsToCollect.h"
#include <SFML/Graphics.hpp>

//-----class section-----
class BulletsGift : public ItemsToCollect
{
public:
    BulletsGift(std::string name, const sf::Vector2f& position);
    ~BulletsGift() = default;
};
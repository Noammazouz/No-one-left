#pragma once

//-----include section-----
#include "ItemsToCollect.h"

//-----class section-----
class MedkitGift : public ItemsToCollect
{
public:
	MedkitGift(const std::string& name, const sf::Vector2f& position);
	virtual ~MedkitGift() = default;
};
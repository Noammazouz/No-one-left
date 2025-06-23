#pragma once

//-----include section-----
#include "ItemsToCollect.h"
#include "Const.h"
#include <SFML/Graphics.hpp>

//-----class section-----
class Bullets : public ItemsToCollect
{
public:
    Bullets(std::string name, const sf::Vector2f& position, BulletOwner owner = BulletOwner::PLAYER);
    ~Bullets() = default;
    BulletOwner getOwner() const;
    void setOwner(BulletOwner owner);

private:
    BulletOwner m_owner;
};
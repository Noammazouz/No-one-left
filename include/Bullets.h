#pragma once

//-----include section-----
#include "ItemsToCollect.h"
#include <SFML/Graphics.hpp>
#include "Const.h"

// Forward declarations
class Player;
class Enemy;

//-----enums section-----
enum class BulletOwner
{
    PLAYER,
    ENEMY
};

//-----class section-----
class Bullets : public ItemsToCollect
{
public:
    Bullets(std::string name,sf::Vector2f position);
    ~Bullets() = default;

};
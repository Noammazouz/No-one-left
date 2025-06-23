#pragma once

//-----include section-----
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

//---forward declaration---
class Bullets;

//-----enums section-----
enum class BulletOwner;

//-----class section-----
class AttackBehavior
{
public:
    virtual ~AttackBehavior() = default;
    virtual void Attack(sf::Vector2f position, sf::Vector2f direction, std::vector<std::unique_ptr<Bullets>>& bullets, BulletOwner owner) = 0;
};
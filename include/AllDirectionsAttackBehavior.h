#pragma once

//-----include section-----
#include "AttackBehavior.h"
#include "Projectile.h"
#include "Const.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

//-----class section-----
class AllDirectionsAttackBehavior : public AttackBehavior
{
public:
    AllDirectionsAttackBehavior() = default;
    virtual ~AllDirectionsAttackBehavior() = default;

    virtual std::vector<sf::Vector2f> Attack(sf::Vector2f position) override;
};
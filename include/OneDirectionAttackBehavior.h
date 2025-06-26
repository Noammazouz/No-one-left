#pragma once

//-----includes section-----
#include "AttackBehavior.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

//-----class section-----
class OneDirectionAttackBehavior : public AttackBehavior
{
public:
    OneDirectionAttackBehavior() = default;
    virtual ~OneDirectionAttackBehavior() = default;

    virtual std::vector<sf::Vector2f> Attack(sf::Vector2f position) override;
};
#pragma once

//-----includes section-----
#include "AttackBehavior.h"
#include "Bullets.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

//-----class section-----
class OneDirectionAttackBehavior : public AttackBehavior
{
public:
    OneDirectionAttackBehavior() = default;
    virtual ~OneDirectionAttackBehavior() = default;

    virtual void Attack(sf::Vector2f position, sf::Vector2f direction, std::vector<std::unique_ptr<Bullets>>& bullets) override;
};
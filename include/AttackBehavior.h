#pragma once  

//-----include section-----  
#include <SFML/Graphics.hpp>  
#include <vector>  
#include <memory>  
#include "Const.h"

//---forward declaration---  
class Projectile;  

//-----class section-----
class AttackBehavior
{
public:
    virtual ~AttackBehavior() = default;
    virtual void Attack(sf::Vector2f position, sf::Vector2f direction, std::vector<std::unique_ptr<Projectile>>& projectile, BulletOwner owner) = 0;
};
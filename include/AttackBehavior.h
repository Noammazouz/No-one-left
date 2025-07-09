#pragma once  

//-----include section-----  
#include <SFML/Graphics.hpp>  
#include <vector>  
#include <memory>  
#include "Const.h"
 
class Projectile;  

//-----class section-----
class AttackBehavior
{
public:
    virtual ~AttackBehavior() = default;
    virtual std::vector<sf::Vector2f> Attack(sf::Vector2f position) = 0;
protected:
    std::vector<sf::Vector2f> m_directrions;
};
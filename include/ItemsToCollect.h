#pragma once

#include "StaticObject.h"

class ItemsToCollect : public StaticObject  
{  
public:  
   ItemsToCollect(sf::Vector2f position); // Updated constructor to match the argument list in Bullets.cpp  
   ~ItemsToCollect() = default;  
};
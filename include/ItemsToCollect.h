#pragma once  

//-----include section-----  
#include "StaticObject.h"  

//-----class section-----  
class ItemsToCollect : public StaticObject  
{    
public:    
 ItemsToCollect(const std::string& name, const sf::Vector2f& position);
 ~ItemsToCollect() = default;    
};
#pragma once  

//-----include section-----  
#include "StaticObject.h"  

//-----class section-----  
class ItemsToCollect : public StaticObject  
{    
public:    
 ItemsToCollect(const sf::Vector2f& position, const std::string& name); 
 ~ItemsToCollect() = default;    

 virtual void collide(GameObject& otherObject) override;    
 virtual void enemyCollide(Enemy& otherObject) override;    
 virtual void playerCollide(Player& otherObject) override;    
 virtual void explosionCollide(Explosion& otherobject) override;    
};
#pragma once  

//-----include section-----  
#include "UpdateableObject.h"  
#include "Enemy.h"  
#include "Player.h"  
#include "Explosion.h"  
#include "Const.h"  
#include "../../../../../SFML/SFML-2.6.1/include/SFML/System/Vector2.hpp" // copilot fix  
#include "../../../../../SFML/SFML-2.6.1/include/SFML/System/Time.hpp" // Fix for sf::Time  


//-----class section-----  
class Projectile : public UpdateableObject  
{  
public:  
  Projectile(sf::Vector2f position, sf::Vector2f dir = sf::Vector2f(1, 0),  
      float spd = 300.0f, int damage = 1);  
  ~Projectile() override = default;  

  void update(sf::Time deltaTime, sf::Vector2f playerPos) override;  
  void setDirection(sf::Vector2f dir);  
  void setSpeed(float spd);  
  sf::Vector2f getDirection() const;  
  float getSpeed() const;  
  bool getIsActive() const;  
  void setActive(bool active);  
  bool isOutOfMap() const;  

  int getDamage() const;  
  bool isExpired() const;  

private:  
  sf::Vector2f direction;  
  float speed;  
  bool isActive;  
  int damage;  
  float elapsedTime;   
};

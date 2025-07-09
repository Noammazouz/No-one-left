#pragma once  

//-----include section-----  
#include "UpdateableObject.h"  
#include "Enemy.h"  
#include "Player.h"  
#include "Const.h"

//-----class section-----  
class Projectile : public UpdateableObject  
{  
public:  
	  Projectile(sf::Vector2f position, sf::Vector2f direction,
				 BulletOwner owner, const std::string& weaponName);
	  ~Projectile() override = default;  

	  void update(sf::Time deltaTime, sf::Vector2f playerPos) override;  
	  void setDirection(sf::Vector2f dir); 
	  sf::Vector2f getDirection() const;   
	  bool getIsActive() const;  
	  void setActive(bool active);  
	  bool isExpired() const;  

	  static void registerBulletCollisions();

	  BulletOwner getOwner() const;

private:
	  sf::Vector2f m_direction;    
	  bool isActive;  
	  float m_elapsedTime;   
	  BulletOwner m_owner;
	  std::string m_weaponName;

	  static bool g_bulletCollisionRegistered;
};

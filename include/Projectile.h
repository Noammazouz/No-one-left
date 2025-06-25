#pragma once  

//-----include section-----  
#include "UpdateableObject.h"  
#include "Enemy.h"  
#include "Player.h"  
#include "Explosion.h"  
#include "Const.h"

//-----class section-----  
class Projectile : public UpdateableObject  
{  
public:  
	  Projectile(sf::Vector2f position, sf::Vector2f direction, BulletOwner owner);  
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

	  static void registerBulletCollisions();

	  BulletOwner getOwner() const;

private:
	  sf::Vector2f m_direction;  
	  float speed;  
	  bool isActive;  
	  int damage;  
	  float m_elapsedTime;   
	  BulletOwner m_owner;

	  static bool g_bulletCollisionRegistered;
};

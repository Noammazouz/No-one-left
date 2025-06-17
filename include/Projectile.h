#pragma once

#include "UpdateableObject.h"

class Projectile : public UpdateableObject 
{
public:
	Projectile(std::string name, sf::Vector2f pos, int damage, int lifetime);
	~Projectile() override;
	void update(float deltaTime) override;
	void render() const override;
	int getDamage() const;
	bool isExpired() const;
}
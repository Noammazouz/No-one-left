#pragma once

//-----include section-----
#include "StaticObject.h"

//-----class section-----
class Obstacles : public StaticObject 
{
public:
	Obstacles(const sf::Vector2f& position, std::string name);
	~Obstacles() = default;

	void decLife();

private:
	int m_life = NUM_OF_LIFE_OBSTACLE;
};

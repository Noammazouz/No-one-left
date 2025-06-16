#pragma once

//-----include section-----
#include "GameObject.h"

//-----class section-----
class UpdateableObject : public GameObject
{
public:
	UpdateableObject();
	UpdateableObject(sf::Vector2f position, const sf::Texture& texture);
	virtual ~UpdateableObject() = default;

	virtual void update(sf::Time deltaTime, sf::Vector2f playerPos = {0,0}) = 0;
	virtual bool checkCollision(GameObject& otherObject) { return false; };

	sf::Vector2f getPrevLocation() const;

protected:
	void setPrevLocation(const sf::Vector2f& position);

private:
	sf::Vector2f m_starting_position;
	sf::Vector2f m_prevLocation;
};

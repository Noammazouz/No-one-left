#pragma once

//-----include section-----
#include "GameObject.h"

//-----class section-----
class UpdateableObject : public GameObject
{
public:
	UpdateableObject();
	UpdateableObject(sf::Vector2f position, std::string name);
	virtual ~UpdateableObject() = default;

	virtual void update(sf::Time deltaTime, sf::Vector2f playerPos = {0,0}) = 0;
	virtual bool checkCollision(GameObject& otherObject);

	sf::Vector2f getPrevLocation() const;

protected:
	void setPrevLocation(const sf::Vector2f& position);
	void updatePosition(const sf::Vector2f& direction);
	void setRotation(const sf::Vector2f& direction);

private:
	sf::Vector2f m_startingPosition;
	sf::Vector2f m_prevLocation;
	float m_targetAngle = 0.f; //Target angle for rotation
};

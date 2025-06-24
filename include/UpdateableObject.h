#pragma once

//-----include section-----
#include "GameObject.h"
//#include <SFML/System/Time.hpp>
#include <time.h>

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
	sf::Vector2f getStartingPosition() const;

protected:
	void setPrevLocation(const sf::Vector2f& position);
	void updatePosition(const sf::Vector2f& direction);
	void setRotation(const sf::Vector2f& direction);

	std::vector<sf::IntRect> m_frames;
	sf::Clock m_animClock;
	int currentPlayerFrame = 0;

	void updateFrames(const sf::Vector2f& direction, const float frameTime, const int numberOfFrames);

private:
	sf::Vector2f m_startingPosition;
	sf::Vector2f m_prevLocation;
	float m_targetAngle = 0.f; //Target angle for rotation
};

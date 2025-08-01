#pragma once

//-----include section-----
#include "GameObject.h"
#include <time.h>
#include <numbers>

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
	void handleDeath();
	void beginDying(int width, int height, int frameTime, const std::string& name);

	void changeSpriteAnimation(const std::string& name,
							   const int frameWidth,
							   const int frameHeight);

protected:
	void setPrevLocation(const sf::Vector2f& position);
	void updatePosition(const sf::Vector2f& direction);
	void setRotation(const sf::Vector2f& direction);
	void resetClock();

	std::vector<sf::IntRect> m_frames;
	sf::Clock m_animClock;
	int m_currentObjectFrame = 0;
	int m_numberOfFrames; //Number of frames for animation.

	virtual void updateFrames(const sf::Vector2f& direction, const float frameTime, const int numberOfFrames);
	void set_frames(const int framesNumber, const sf::Vector2f position,
				    const int frameWidth, const int frameHeight);

	float m_deathDuration = 0.5f; //Time to play the animation.

	void startDying(const std::string& name, const int widthFrame, const int heightFrame);

private:
	sf::Clock m_rotationClock;
	sf::Vector2f m_startingPosition;
	sf::Vector2f m_prevLocation;
	float m_targetAngle = 0.f; //Target angle for rotation.
};

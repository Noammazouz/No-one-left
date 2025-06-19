//-----include section-----
#include "UpdateableObject.h"
#include <iostream>
#include <SFML/System.hpp>

//-----functions section------
//-----------------------------------------------------------------------------
UpdateableObject::UpdateableObject() 
	: GameObject()
{}

//-----------------------------------------------------------------------------
UpdateableObject::UpdateableObject(sf::Vector2f position, std::string name)
	: GameObject(name, position), m_startingPosition(position), m_prevLocation(position)
{}

//-----------------------------------------------------------------------------
bool UpdateableObject::checkCollision(GameObject& otherObject)
{
	if (getBounds().intersects(otherObject.getBounds()))
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
sf::Vector2f UpdateableObject::getPrevLocation() const
{
	return m_prevLocation;
};

//-----------------------------------------------------------------------------
void UpdateableObject::setPrevLocation(const sf::Vector2f& pos)
{
    m_prevLocation = pos;
}

//-----------------------------------------------------------------------------
void UpdateableObject::setRotation(const sf::Vector2f& direction)
{
    static sf::Clock rotationClock;
    float deltaTime = rotationClock.restart().asSeconds();

    //Ignore zero direction
    if (direction == sf::Vector2f(0.f, 0.f)) return;

    //Normalize direction vector
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0.f) return;
    sf::Vector2f normDir = direction / length;

    //Map normalized direction to fixed 8 angles (degrees, 0? = Up)
    //Use thresholds to detect closest direction
    if (normDir.x > 0.7f && normDir.y < -0.7f)          m_targetAngle = 45.f;   // Up-Right
    else if (normDir.x > 0.7f && normDir.y > 0.7f)      m_targetAngle = 135.f;  // Down-Right
    else if (normDir.x < -0.7f && normDir.y > 0.7f)     m_targetAngle = 225.f;  // Down-Left
    else if (normDir.x < -0.7f && normDir.y < -0.7f)    m_targetAngle = 315.f;  // Up-Left
    else if (normDir.x > 0.5f)                          m_targetAngle = 90.f;   // Right
    else if (normDir.x < -0.5f)                         m_targetAngle = 270.f;  // Left
    else if (normDir.y < -0.5f)                         m_targetAngle = 0.f;    // Up
    else if (normDir.y > 0.5f)                          m_targetAngle = 180.f;  // Down

    //Smooth rotation toward target angle
    float currentAngle = m_pic.getRotation();
    float deltaAngle = std::fmod(m_targetAngle - currentAngle + 540.f, 360.f) - 180.f;
    float rotationStep = ROTATION_SPEED * deltaTime;

    if (std::abs(deltaAngle) < rotationStep) currentAngle = m_targetAngle;
    else currentAngle += (deltaAngle > 0.f ? 1.f : -1.f) * rotationStep;

    //Normalize current angle to [0, 360)
    if (currentAngle < 0.f) currentAngle += 360.f;
    else if (currentAngle >= 360.f) currentAngle -= 360.f;

    m_pic.setRotation(currentAngle);
}

//-----------------------------------------------------------------------------
void UpdateableObject::updatePosition(const sf::Vector2f& direction)
{
    float left_corner = direction.x + m_pic.getPosition().x - ResourcesManager::getInstance().getTexture("Player").getSize().x / 2.f;
    float bottom_corner = direction.y + m_pic.getPosition().y + ResourcesManager::getInstance().getTexture("Player").getSize().y / 2.f;
    float up_corner = direction.y + m_pic.getPosition().y - ResourcesManager::getInstance().getTexture("Player").getSize().y / 2.f;
    float right_corner = direction.x + m_pic.getPosition().x + ResourcesManager::getInstance().getTexture("Player").getSize().x / 2.f;


    if (left_corner > 0 && up_corner > 0 && bottom_corner < MAP_HEIGHT && right_corner < MAP_WIDTH)
    {
        //m_pic.setTextureRect(frame[current_frame]);
        m_pic.move(direction);
    }
}
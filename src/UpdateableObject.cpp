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
{
    m_animClock.restart();
}

//-----------------------------------------------------------------------------
bool UpdateableObject::checkCollision(GameObject& otherObject)
{
	if (getBounds().intersects(otherObject.getBounds())) return true;
	return false;
}

//-----------------------------------------------------------------------------
sf::Vector2f UpdateableObject::getPrevLocation() const
{
	return m_prevLocation;
};

//-----------------------------------------------------------------------------
sf::Vector2f UpdateableObject::getStartingPosition() const
{
	return m_startingPosition;
};

//-----------------------------------------------------------------------------
void UpdateableObject::setPrevLocation(const sf::Vector2f& pos)
{
    m_prevLocation = pos;
}

//-----------------------------------------------------------------------------
void UpdateableObject::setRotation(const sf::Vector2f& direction)
{
    //Ignore zero‐length vectors
    if (direction == DEFAULT_VECTOR) return;

    //Compute the angle in degrees: atan2 returns radians, so multiply by 180/π.
    float angle = std::atan2(direction.y, direction.x) * 180.f / std::numbers::pi;

    //(Optionally add an offset so 0° points “up” instead of “right”)
    angle -= 90.f;  

    //Smoothly interpolate current rotation → target rotation
    float current = m_pic.getRotation();
    float delta   = std::fmod(angle - current + 540.f, 360.f) - 180.f;
    float step    = ROTATION_SPEED * m_rotationClock.restart().asSeconds();

    if (std::abs(delta) < step) current = angle;
    else current += (delta > 0 ? step : -step);

    //Normalize to [0,360)
    if (current < 0)   current += 360.f;
    if (current >=360) current -= 360.f;

    m_pic.setRotation(current);
}

//-----------------------------------------------------------------------------
void UpdateableObject::updatePosition(const sf::Vector2f& direction)
{
    //get sprite bounds (already reflects texture rect).
    sf::FloatRect bounds = m_pic.getGlobalBounds();

    //calculate the corners of the window.
    float left_corner = m_pic.getPosition().x + direction.x - bounds.width / 2.f;
    float up_corner = m_pic.getPosition().y + direction.y - bounds.height / 2.f;
    float right_corner = left_corner + bounds.width;
    float bottom_corner = up_corner + bounds.height;

	//Check if the m_pic is in the window bounds.
    if (left_corner > 0 && up_corner > 0 && bottom_corner < MAP_HEIGHT && right_corner < MAP_WIDTH)
    {
        m_pic.move(direction);
    }
}

//-----------------------------------------------------------------------------
void UpdateableObject::updateFrames(const sf::Vector2f& direction, const float frameTime, const int numberOfFrames)
{
    if (direction != DEFAULT_VECTOR)
    {
        if (m_animClock.getElapsedTime().asSeconds() >= frameTime)
        {
            m_currentObjectFrame = (m_currentObjectFrame + 1) % numberOfFrames;
            m_animClock.restart();
            m_pic.setTextureRect(m_frames[m_currentObjectFrame]);
        }
    }
    else if (m_currentObjectFrame != 0)
    {
        m_currentObjectFrame = 0;
        m_pic.setTextureRect(m_frames[0]);
    }
}

//-----------------------------------------------------------------------------
void UpdateableObject::set_frames(const int framesNumber, const sf::Vector2f position, 
                                  const int frameWidth, const int frameHeight)
{
    m_frames.clear();
    m_frames.reserve(m_numberOfFrames);
    for (int frameNumber = 0; frameNumber < m_numberOfFrames; frameNumber++)
    {
        m_frames.emplace_back(sf::IntRect(frameNumber * frameWidth, 0, frameWidth, frameHeight));
    }
    m_pic.setTextureRect(m_frames[m_currentObjectFrame]); //set for the first frame at first.
    m_pic.setOrigin(frameWidth / 2, frameHeight / 2); //Set origin to center.
    m_pic.setPosition(position);
}

//-----------------------------------------------------------------------------
void UpdateableObject::changeSpriteAnimation(const std::string& name, 
                                             const int frameWidth, 
                                             const int frameHeight)
{
    auto samePosition = m_pic.getPosition();
    auto& texture = ResourcesManager::getInstance().getTexture(name);
    m_pic.setTexture(texture);
    m_numberOfFrames = m_pic.getTexture()->getSize().x / frameWidth; //Calculate number of frames based on texture width.
    m_pic.setRotation(180.f); //Set initial rotation to face down.
    set_frames(m_numberOfFrames, samePosition, frameWidth, frameHeight);
}

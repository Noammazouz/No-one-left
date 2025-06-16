//-----include section-----
#include "GameObject.h"
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
GameObject::GameObject()
{}

//-----------------------------------------------------------------------------
GameObject::GameObject(const sf::Texture& texture, const sf::Vector2f& position, 
                       float width, float height)
{
    m_pic.setTexture(texture);
	m_pic.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2); // Set origin to center
    m_pic.setPosition(position);
}

//-----------------------------------------------------------------------------
void GameObject::draw(sf::RenderWindow& window)
{
    window.draw(m_pic);
}

//-----------------------------------------------------------------------------
sf::Vector2f GameObject::getObjPosition() const
{
	return m_pic.getPosition();
}

//-----------------------------------------------------------------------------
void GameObject::setRotation(sf::Vector2f direction)
{
	static sf::Clock rotationClock; // Clock persists across calls
	float deltaTime = rotationClock.restart().asSeconds();


	if (direction == sf::Vector2f(-1, 0))
	{
		m_targetAngle = 270.f;
	}
	else if (direction == sf::Vector2f(1, 0))
	{
		m_targetAngle = 90.f;
	}
	else if (direction == sf::Vector2f(0, -1))
	{
		m_targetAngle = 0.f;
	}
	else if (direction == sf::Vector2f(0, 1))
	{
		m_targetAngle = 180.f;
	}
	//else if (up && right)
	//{
	//	m_direction = sf::Vector2f(0, -0.5f);
	//	m_targetAngle = 45.f; // Maintain current angle
	//}

	// --- Smooth rotation towards m_targetAngle ---
	float currentAngle = m_pic.getRotation();

	// Normalize angle difference to [-180, 180]
	float deltaAngle = std::fmod(m_targetAngle - currentAngle + 540.f, 360.f) - 180.f;

	// Compute step
	float rotationStep = ROTATION_SPEED * deltaTime;

	// Apply smooth turn
	if (std::abs(deltaAngle) < rotationStep)
		currentAngle = m_targetAngle;
	else
		currentAngle += (deltaAngle > 0 ? 1 : -1) * rotationStep;

	m_pic.setRotation(currentAngle);
}

//-----------------------------------------------------------------------------
void GameObject::updatePosition(sf::Vector2f direction)
{
	float left_corner = direction.x + m_pic.getPosition().x - ResourcesManager::getInstance().getTexture("Player").getSize().x / 2.f;
	float bottom_corner = direction.y + m_pic.getPosition().y + ResourcesManager::getInstance().getTexture("Player").getSize().y / 2.f;
	float up_corner = direction.y + m_pic.getPosition().y - ResourcesManager::getInstance().getTexture("Player").getSize().y / 2.f;
	float right_corner = direction.x + m_pic.getPosition().x + ResourcesManager::getInstance().getTexture("Player").getSize().x / 2.f;


	if (left_corner > 0 && up_corner > 0 && bottom_corner < MAP_HEIGHT && right_corner < MAP_WIDTH)
	{
		m_pic.move(direction);
	}
}
#include "Player.h"
#include <iostream>


int Player::m_lives = NUM_OF_LIVES;
//---------------------------------
int Player::m_score = 0;
//---------------------------------
Player::Player()
	: UpdateableObject(), m_present(DEFAULT)
{
}
//-------------------------------------
Player::Player(sf::Vector2f position, const sf::Texture& texture, float CELL_WIDTH, float CELL_HEIGHT)
	: UpdateableObject(position, texture, CELL_WIDTH, CELL_HEIGHT), m_present(DEFAULT)
{
}
//-------------------------------------
void Player::update(sf::Time deltaTime)
{
	this->setPrevLocation(this->getPosition());
	this->updatePosition(m_direction * PLAYER_SPEED * deltaTime.asSeconds());
}
//-------------------------------------
void Player::setDirection(sf::Vector2f /*position*/)
{
	if (checkDeriction())
	{
		// Get the current key being pressed and update movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_direction = sf::Vector2f(-1, 0);
			this->mirrorImage(m_direction);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_direction = sf::Vector2f(1, 0);
			this->mirrorImage(m_direction);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_direction = sf::Vector2f(0, -1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_direction = sf::Vector2f(0, 1);
		}
	}
	else
	{
		// If no movement keys are pressed, stop the player
		m_direction = sf::Vector2f(0, 0);
	}
}
//-------------------------------------
void Player::collide(GameObject& otherObject)
{
	otherObject.playerCollide(*this);
}
//-------------------------------------
void Player::guardCollide(Guard& /*otherObject*/)
{
}
//-------------------------------------
void Player::explosionCollide(Explosion& /*otherobject*/)
{
	this->setPosition(this->getStartingPosition());
	decLife();
}
//-------------------------------------
void Player::decLife()
{
	m_lives--;
}
//-------------------------------------
int Player::getLife()
{
	return m_lives;
}
//-------------------------------------
void Player::setWin(bool win)
{
	m_win = win;
}
//-------------------------------------
bool Player::getWin() const
{
	return m_win;
}
//-----------------------------
const Present& Player::getPresent() const
{
	return m_present;
}
//-------------------------------
void Player::setPresent(Present present)
{
	m_present = present;
}
//-------------------------------------
void Player::incLife()
{
	if (m_lives < NUM_OF_LIVES)
	{
		m_lives++;
	}
}
//-------------------------------------
int Player::getScore()
{
	return m_score;
}
//----------------------------
void Player::setScore(int score)
{
	m_score += score;
}
//-------------------------------------
bool Player::checkDeriction()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}
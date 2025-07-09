#include "Bomb.h"
#include "ResourcesManager.h"
#include "Const.h" // BOMB_TIME
#include <cmath>
#include "GamePlay.h"

Bomb::Bomb(sf::Vector2f position, GamePlay* gameplay)
	:UpdateableObject(position, BOMB_NAME), m_timer(sf::seconds(BOMB_TIME)), m_gameplay(gameplay)
{
	m_numberOfFrames = m_pic.getTexture()->getSize().x / BOMB_WIDTH;
	set_frames(m_numberOfFrames, position);
}

void Bomb::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
	m_timer -= deltaTime;
	updateFrames({ 0,0 }, BOMB_FRAME_TIME, m_numberOfFrames);
	if (m_timer <= sf::Time::Zero)
	{
		m_gameplay->addExplosion(this->getPosition());
		this->setLife(true);
	}
}

void Bomb::updateFrames(const sf::Vector2f& direction, const float frameTime, const int numberOfFrames)
{
	if (m_animClock.getElapsedTime().asSeconds() >= frameTime)
	{
		currentPlayerFrame = (currentPlayerFrame + 1) % numberOfFrames;
		m_animClock.restart();
		m_pic.setTextureRect(m_frames[currentPlayerFrame]);
	}
}

void Bomb::set_frames(const int framesNumber, const sf::Vector2f position)
{
	m_frames.clear();
	m_frames.reserve(m_numberOfFrames);
	for (int frameNumber = 0; frameNumber < m_numberOfFrames; frameNumber++)
	{
		m_frames.emplace_back(sf::IntRect(frameNumber * BOMB_WIDTH, 0, BOMB_WIDTH, BOMB_HEIGHT));
	}

	m_pic.setTextureRect(m_frames[currentPlayerFrame]); //set for the first frame at first.
	m_pic.setOrigin(BOMB_WIDTH / 2, BOMB_HEIGHT / 2); //Set origin to center.
	m_pic.setPosition(position);
}



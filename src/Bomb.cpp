#include "Bomb.h"
#include "ResourcesManager.h"
#include "Const.h" // BOMB_TIME
#include <cmath>
#include "GamePlay.h"

Bomb::Bomb(sf::Vector2f position, GamePlay* gameplay)
	:UpdateableObject(position, BOMB_NAME), m_timer(sf::seconds(BOMB_TIME)), m_gameplay(gameplay)
{
	m_numberOfFrames = m_pic.getTexture()->getSize().x / BOMB_WIDTH;
	set_frames(m_numberOfFrames, position, BOMB_WIDTH, BOMB_HEIGHT);
}

void Bomb::update(sf::Time deltaTime, sf::Vector2f /*playerPos*/)
{
	m_timer -= deltaTime;
	updateFrames(DEFAULT_DIRECTION, BOMB_FRAME_TIME, m_numberOfFrames);
	if (m_timer <= sf::Time::Zero)
	{
		m_gameplay->addExplosion(this->getPosition());
		this->setLife(true);
	}
}




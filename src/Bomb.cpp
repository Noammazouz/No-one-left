#include "Bomb.h"
#include "ResourcesManager.h"
#include "Const.h" // BOMB_TIME
#include <cmath>
#include "GamePlay.h"

Bomb::Bomb(sf::Vector2f position, GamePlay* gameplay)
	:UpdateableObject(position, BOMB_NAME), m_timer(sf::seconds(BOMB_TIME)), m_gameplay(gameplay)
{
}

void Bomb::update(sf::Time deltaTime, sf::Vector2f playerPos)
{
	m_timer -= deltaTime;
	if (m_timer <= sf::Time::Zero)
	{
		m_gameplay->addExplosion(this->getPosition());
		this->setLife(true);
	}
}



#pragma once
#include "UpdateableObject.h"
#include <SFML/System.hpp>

class GamePlay;

class Bomb : public UpdateableObject
{
public:
	Bomb(sf::Vector2f position,GamePlay* gamePlay);
	void update(sf::Time deltaTime, sf::Vector2f playerPos);

protected:
	void updateFrames(const sf::Vector2f& direction, const float frameTime, const int numberOfFrames) override;
	void set_frames(const int framesNumber, const sf::Vector2f position) override;
private:
	sf::Time m_timer;
	GamePlay* m_gameplay;
};
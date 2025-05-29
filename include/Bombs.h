#pragma once

#include "UpdateableObject.h"


class Bombs : public UpdateableObject
{
public:
	Bombs(sf::Vector2f position, const sf::Texture& texture);

	virtual void update(sf::Time deltaTime) override;
	virtual void setDirection(sf::Vector2f position) override;
	virtual void collide(GameObject& otherObject) override;
	virtual void guardCollide(Guard& otherObject) override;

	sf::Time getTimer() const override;
	bool getExpo() const override;

private:
	sf::Time m_timer;
	bool m_isExploded=false;
};


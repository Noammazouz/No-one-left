#pragma once
#include "UpdateableObject.h"

class GameObject;

class Player : public UpdateableObject
{
public:
	Player();
	Player(sf::Vector2f position, const sf::Texture& texture, float CELL_WIDTH, float CELL_HEIGHT);

	virtual void update(sf::Time deltaTime) override;
	virtual void setDirection(sf::Vector2f position) override;

	virtual void collide(GameObject& otherObject) override;
	virtual void guardCollide(Guard& otherObject) override;
	virtual void explosionCollide(Explosion& otherobject) override;

	void setWin(bool win);
	bool getWin() const;
    int getScore();
	void setScore(int score);
	void decLife();
	void incLife();
	static int getLife();
	const Present& getPresent() const;
	void setPresent(Present present);

	~Player() = default;

private:
	bool checkDeriction();

	sf::Vector2f m_direction;

	static int m_lives;
	static int m_score;
	bool m_win = false;

	Present m_present;
};
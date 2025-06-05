#pragma once

//-----include section-----
#include "UpdateableObject.h"

class GameObject;

//-----class section-----
class Player : public UpdateableObject
{
public:
	Player();
	Player(sf::Vector2f position, const sf::Texture& texture);
	~Player() = default;

	virtual void update(sf::Time deltaTime) override;
	virtual void setDirection(sf::Vector2f position) override;

	virtual void collide(GameObject& otherObject) override;
<<<<<<< HEAD
	virtual void guardCollide(Enemy& otherObject) override;
=======
	virtual void enemyCollide(Enemy& otherObject) override;
>>>>>>> ebd655d612b4d4a5151048c1ea5ab80f03a4dc05
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

private:
	bool checkDeriction();

	sf::Vector2f m_direction;

	static int m_lives;
	static int m_score;
	bool m_win = false;

	Present m_present;
};
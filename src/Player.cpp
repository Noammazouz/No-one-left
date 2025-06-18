//-----include section-----
#include "Player.h"
#include "Factory.h"

//-----functions section------
//-----------------------------------------------------------------------------
//Defines the static members.
int Player::m_lives = NUM_OF_LIVES;
int Player::m_score = 0;

//-----------------------------------------------------------------------------
Player::Player()
	: UpdateableObject()
{}

//-----------------------------------------------------------------------------
Player::Player(sf::Vector2f position, std::string name)
	: UpdateableObject(position, name)
{}

//-----------------------------------------------------------------------------
void Player::update(sf::Time deltaTime, sf::Vector2f /*playerPos*/)
{
	setDirection();
	this->setPrevLocation(this->getPosition());
	this->updatePosition(m_direction * PLAYER_SPEED * deltaTime.asSeconds());
}

//-----------------------------------------------------------------------------
//void Player::setDirection()
//{
//	if (checkDirection())
//	{
//		// Get the current key being pressed and update movement
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//		{
//			m_direction = sf::Vector2f(-1, 0);
//			this->mirrorImage(m_direction);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//		{
//			m_direction = sf::Vector2f(1, 0);
//			this->mirrorImage(m_direction);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//		{
//			m_direction = sf::Vector2f(0, -1);
//		}
//		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//		{
//			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) m_direction = sf::Vector2f(-1, 1);
//			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_direction = sf::Vector2f(1, 1);
//			else m_direction = sf::Vector2f(0, 1);
//		}
//		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//		{
//			m_direction = sf::Vector2f(0, 0);
//		}
//	}
//	else
//	{
//		// If no movement keys are pressed, stop the player
//		m_direction = sf::Vector2f(0, 0);
//	}
//
//	this->setRotation(m_direction);
//}

void Player::setDirection()
{
	if (!checkDirection())
	{
		m_direction = sf::Vector2f(0, 0);
		this->setRotation(m_direction);
		return;
	}

	sf::Vector2f newDir(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) newDir.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) newDir.x += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) newDir.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) newDir.y += 1.f;

	//Normalize direction if moving diagonally
	if (newDir != sf::Vector2f(0.f, 0.f))
		newDir /= std::sqrt(newDir.x * newDir.x + newDir.y * newDir.y);

	m_direction = newDir;

	this->setRotation(m_direction);
}

//------------------------------------------------------------------------------
bool Player::checkDirection()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		   sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		   sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		   sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}

//-----------------------------------------------------------------------------
void Player::decLife()
{
	m_lives--;
}

//-----------------------------------------------------------------------------
int Player::getLife()
{
	return m_lives;
}

//-----------------------------------------------------------------------------
void Player::setWin(bool win)
{
	m_win = win;
}

//-----------------------------------------------------------------------------
bool Player::getWin() const
{
	return m_win;
}

//-----------------------------------------------------------------------------
sf::Vector2f Player::getPos() const
{
	return getPosition();
}

//------------------------------------------------------------------------------
void Player::incLife()
{
	if (m_lives < NUM_OF_LIVES) m_lives++;
}

//------------------------------------------------------------------------------
int Player::getScore()
{
	return m_score;
}

//------------------------------------------------------------------------------
void Player::setScore(int score)
{
	m_score += score;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//void Plyer::registerCollision()
//{
//	static bool registered = false;
//	if (registered) return; //only register once
//
//	auto& factory = CollisionFactory::getInstance();
//
//	//register the collision handlers
//	factory.registerSymetricCollision<Player, Enemy>([](Player& player, Enemy& enemy) { 
//		Player& p = static_cast<Player&>(player);
//		std::cout << "Player hit by Enemy!" << std::endl;
//		p.decLife();
//		p.setPosition(p.getStartingPosition());
//	});
//
//	factory.registerSymetricCollision<Player, Wall>([](Player& player, Wall& wall) { 
//		Player& p = static_cast<Player&>(player);
//		std::cout << "Player hit a Wall!" << std::endl;
//		p.setPosition(p.getPrevLocation()); // revert to previous position
//	});
//
//	factory.registerSymetricCollision<Player, Explosion>([](Player& player, Explosion& explosion) { 
//		Player& p = static_cast<Player&>(player);
//		std::cout << "Player hit an Explosion!" << std::endl;
//		p.decLife();
//		p.setPosition(p.getStartingPosition());
//	});
//
//	registered = true;
//	std::cout << "Player collisions registered." << std::endl;
//}

//------------------------------------------------------------------------------
//Auto-regiteration helper - runs when first Player is created.
//static bool g_playerColliosionRegistered = []()
//{
//	Player::registerCollision();
//	return true;
//}
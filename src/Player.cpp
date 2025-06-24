//-----include section-----
#include "Player.h"
#include "CollisionFactory.h"
#include "Factory.h"
#include <OneDirectionAttackBehavior.h>
#include <AllDirectionsAttackBehavior.h>

//-----functions section------
//-----------------------------------------------------------------------------
//Defines the static members.
int Player::m_score = 0;
int Player::m_bulletCount = NUM_OF_BULLETS;

//-----------------------------------------------------------------------------
Player::Player()
	: UpdateableObject(), m_isShooting(false), /*m_attackBehavior(std::move(std::make_unique<OneDirectionAttackBehavior>())),*/ m_lives(NUM_OF_LIVES)
{}

//-----------------------------------------------------------------------------
Player::Player(sf::Vector2f position, std::string name)
	: UpdateableObject(position, name), m_isShooting(false), /*m_attackBehavior(std::move(std::make_unique<OneDirectionAttackBehavior>())),*/ m_lives(NUM_OF_LIVES)
{
	m_numberOfFrames = m_pic.getTexture()->getSize().x / PLAYER_WIDTH; //Calculate number of frames based on texture width.
	m_pic.setRotation(180.f); //Set initial rotation to face down.
	set_frames(m_numberOfFrames, position);
}

//-----------------------------------------------------------------------------
void Player::update(sf::Time deltaTime, sf::Vector2f /*playerPos*/)
{
	setDirection();
	this->setPrevLocation(this->getPosition());
	this->updatePosition(m_direction * PLAYER_SPEED * deltaTime.asSeconds());
	this->updateFrames(m_direction, PLAYER_FRAME_TIME, m_numberOfFrames);
}

//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
int Player::getNumOfBullets()
{
	return m_bulletCount;
}

//-----------------------------------------------------------------------------
void Player::addBullets(int bullets)
{
	m_bulletCount += bullets;
}

//-----------------------------------------------------------------------------
void Player::decBullets()
{
	if (m_bulletCount > 0)
	{
		m_bulletCount--;
	}
}

//-----------------------------------------------------------------------------
bool Player::isBulletsAvailable()
{
	if (m_bulletCount > 0)
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
sf::Vector2f Player::getCurrentDirection() const
{
	return m_direction;
}

//-----------------------------------------------------------------------------
void Player::handleShooting(std::vector<std::unique_ptr<Projectile>>& bullets)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!m_isShooting)
		{
			doAttack(bullets);
			m_isShooting = true;
		}
	}
	else
	{
		m_isShooting = false;
	}
}

//-----------------------------------------------------------------------------
void Player::setAttackBehavior(std::unique_ptr<AttackBehavior> attackBehavior)
{
	//m_attackBehavior = std::move(attackBehavior);
}

//-----------------------------------------------------------------------------
void Player::doAttack(std::vector<std::unique_ptr<Projectile>>& bullets)
{
	//if (!m_attackBehavior) return;

	int bulletsNeeded = ONE_DIRECTION_BULLET; //default is one direction

	//if (typeid(*m_attackBehavior) == typeid(AllDirectionsAttackBehavior)) //check if attack for all directions
	//{
	//	bulletsNeeded = ALL_DIRECTIONS_BULLETS;
	//}

	if (getNumOfBullets() >= bulletsNeeded)
	{
		sf::Vector2f position = getPos();
		sf::Vector2f direction = getCurrentDirection();

		//m_attackBehavior->Attack(position, direction, bullets);

		for (int bullet = 0; bullet < bulletsNeeded; bullet++)
		{
			decBullets();
		}
	}
}

//------------------------------------------------------------------------------
void handlePlayerEnemyCollision(GameObject& obj1, GameObject& obj2)
{
	// Handle Player vs Enemy collision (bidirectional)
	if (auto* player = dynamic_cast<Player*>(&obj1)) 
	{
		if (auto* enemy = dynamic_cast<Enemy*>(&obj2)) 
		{
			player->decLife();
			//player->setPosition(player->getStartingPosition());
			return;
		}
	}
	// Handle Enemy vs Player collision (reverse direction)
	if (auto* enemy = dynamic_cast<Enemy*>(&obj1)) 
	{
		if (auto* player = dynamic_cast<Player*>(&obj2)) 
		{
			player->decLife();
			//player->setPosition(player->getStartingPosition());
			return;
		}
	}
}

//------------------------------------------------------------------------------
void handlePlayerWallCollision(GameObject& obj1, GameObject& obj2)
{
	//Handle Player vs Wall collision (bidirectional)
	if (auto* player = dynamic_cast<Player*>(&obj1)) 
	{
		if (auto* wall = dynamic_cast<Wall*>(&obj2)) 
		{
			player->setPosition(player->getPrevLocation());
			return;
		}
	}
	// Handle Wall vs Player collision (reverse direction)
	if (auto* wall = dynamic_cast<Wall*>(&obj1)) 
	{
		if (auto* player = dynamic_cast<Player*>(&obj2)) 
		{
			player->setPosition(player->getPrevLocation());
			return;
		}
	}
}

//------------------------------------------------------------------------------
void handlePlayerObstaclesCollision(GameObject& obj1, GameObject& obj2)
{
	//Handle Player vs Wall collision (bidirectional)
	if (auto* player = dynamic_cast<Player*>(&obj1))
	{
		if (auto* wall = dynamic_cast<Obstacles*>(&obj2))
		{
			player->setPosition(player->getPrevLocation());
			return;
		}
	}
	// Handle Wall vs Player collision (reverse direction)
	if (auto* wall = dynamic_cast<Obstacles*>(&obj1))
	{
		if (auto* player = dynamic_cast<Player*>(&obj2))
		{
			player->setPosition(player->getPrevLocation());
			return;
		}
	}
}

//------------------------------------------------------------------------------
void handlePlayerExplosionCollision(GameObject& obj1, GameObject& obj2)
{
	//Handle Player vs Explosion collision (bidirectional)
	if (auto* player = dynamic_cast<Player*>(&obj1)) 
	{
		if (auto* explosion = dynamic_cast<Explosion*>(&obj2)) 
		{
			player->decLife();
			//player->setPosition(player->getStartingPosition());
			return;
		}
	}
	//Handle Explosion vs Player collision (reverse direction)
	if (auto* explosion = dynamic_cast<Explosion*>(&obj1)) 
	{
		if (auto* player = dynamic_cast<Player*>(&obj2)) 
		{
			player->decLife();
			//player->setPosition(player->getStartingPosition());
			return;
		}
	}
}

//------------------------------------------------------------------------------
static bool g_playerCollisionRegistered = []() {
	auto& factory = CollisionFactory::getInstance();
	factory.registerTypedCollision<Player, Enemy>(handlePlayerEnemyCollision);
	factory.registerTypedCollision<Player, Wall>(handlePlayerWallCollision);
	factory.registerTypedCollision<Player, Obstacles>(handlePlayerObstaclesCollision);
	factory.registerTypedCollision<Player, Explosion>(handlePlayerExplosionCollision);
	return true;
	}();
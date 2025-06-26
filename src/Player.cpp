//-----include section-----
#include "Player.h"
#include "CollisionFactory.h"
#include "Factory.h"
#include <OneDirectionAttackBehavior.h>
#include <AllDirectionsAttackBehavior.h>
#include "Enemy.h"
#include "Wall.h"
#include "Explosion.h"
#include "GamePlay.h"

//-----static member initialization-----
//Defines the static members.
int Player::m_score = 0;
int Player::m_bulletCount = NUM_OF_BULLETS;

//-----functions section------
//-----------------------------------------------------------------------------
Player::Player()
	: UpdateableObject(), m_isShooting(false), m_lives(NUM_OF_LIVES)
{}

//-----------------------------------------------------------------------------
void Player::initialization(sf::Vector2f position, std::string name, GamePlay* gamePlay)
{
	auto& texture = ResourcesManager::getInstance().getTexture(name);
	m_pic.setTexture(texture);
	m_numberOfFrames = m_pic.getTexture()->getSize().x / OBJECT_WIDTH; //Calculate number of frames based on texture width.
	m_pic.setRotation(180.f); //Set initial rotation to face down.
	set_frames(m_numberOfFrames, position);

	m_attackBehavior= std::move(std::make_unique<OneDirectionAttackBehavior>());
	m_lives = NUM_OF_LIVES;

	m_gamePlay = gamePlay;
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
void Player::decLife(int decLives)
{
	m_lives -= decLives;
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

//------------------------------------------------------------------------------
void Player::incLife(int addLives)
{
	if (m_lives < NUM_OF_LIVES) m_lives += addLives;
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
void Player::handleShooting()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!m_isShooting)
		{
			m_gamePlay->addProjectile(this->getPosition(), m_attackBehavior->Attack(m_direction), _PLAYER);
			m_isShooting = true;
		}
	}
	else m_isShooting = false;
}

//-----------------------------------------------------------------------------
void Player::setAttackBehavior(std::unique_ptr<AttackBehavior> attackBehavior)
{
	m_attackBehavior = std::move(attackBehavior);
}

//------------------------------------------------------------------------------
void handlePlayerEnemyCollision(GameObject& obj1, GameObject& obj2)
{
	Player* player = nullptr;
	Enemy* enemy = nullptr;

	//Handle Player vs Enemy collision (bidirectional).
	if (auto* tempPlayer = dynamic_cast<Player*>(&obj1)) 
	{
		if (auto* tempEnemy = dynamic_cast<Enemy*>(&obj2))
		{
			player = tempPlayer;
			enemy = tempEnemy;
		}
	}
	//Handle Enemy vs Player collision (reverse direction).
	if (auto* tempEnemy = dynamic_cast<Enemy*>(&obj1)) 
	{
		if (auto* tempPlayer = dynamic_cast<Player*>(&obj2))
		{
			player = tempPlayer;
			enemy = tempEnemy;
		}
	}

	if (player && enemy) 
	{
		player->decLife();
		return;
	}
	else
	{
		std::cout << "Player-Enemy collision not handled properly!" << std::endl;
		return;
	}
}

//------------------------------------------------------------------------------
void handlePlayerWallCollision(GameObject& obj1, GameObject& obj2)
{
	Player* player = nullptr;
	Wall* wall = nullptr;

	//Handle Player vs Wall collision (bidirectional)
	if (auto* tempPlayer = dynamic_cast<Player*>(&obj1)) 
	{
		if (auto* tempWall = dynamic_cast<Wall*>(&obj2)) 
		{
			player = tempPlayer;
			wall = tempWall;
		}
	}
	//Handle Wall vs Player collision (reverse direction)
	if (auto* tempWall = dynamic_cast<Wall*>(&obj1))
	{
		if (auto* tempPlayer = dynamic_cast<Player*>(&obj2))
		{
			player = tempPlayer;
			wall = tempWall;
		}
	}

	if (player && wall) 
	{
		player->setPosition(player->getPrevLocation());
		return;
	}
	else
	{
		std::cout << "Player-Wall collision not handled properly!" << std::endl;
		return;
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
	//Handle Wall vs Player collision (reverse direction)
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
	Player* player = nullptr;
	Explosion* explosion = nullptr;

	//Handle Player vs Explosion collision (bidirectional)
	if (auto* tempPlayer = dynamic_cast<Player*>(&obj1)) 
	{
		if (auto* tempExplosion = dynamic_cast<Explosion*>(&obj2)) 
		{
			player = tempPlayer;
			explosion = tempExplosion;
		}
	}

	//Handle Explosion vs Player collision (reverse direction)
	if (auto* tempExplosion = dynamic_cast<Explosion*>(&obj1))
	{
		if (auto* tempPlayer = dynamic_cast<Player*>(&obj2))
		{
			player = tempPlayer;
			explosion = tempExplosion;
		}
	}

	if (player && explosion) 
	{
		player->decLife(EXPLOSION_DEC_LIVES);
		return;
	}
	else
	{
		std::cout << "Player-Explosion collision not handled properly!" << std::endl;
		return;
	}
}

//------------------------------------------------------------------------------
void handlePlayerRifleGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Player* player = nullptr;
	RifleGift* rifleGift = nullptr;

	//Handle Player vs Rifle Gift collision (bidirectional)
	if (auto* tempPlayer = dynamic_cast<Player*>(&obj1)) 
	{
		if (auto* tempRifleGift = dynamic_cast<RifleGift*>(&obj2)) 
		{
			player = tempPlayer;
			rifleGift = tempRifleGift;
		}
	}
	//Handle Rifle Gift vs Player collision (reverse direction)
	if (auto* tempRifleGift = dynamic_cast<RifleGift*>(&obj1))
	{
		if (auto* tempPlayer = dynamic_cast<Player*>(&obj2))
		{
			player = tempPlayer;
			rifleGift = tempRifleGift;
		}
	}

	if(player && rifleGift) 
	{
		player->changeSpriteAnimation(PLAYER_RIFLE);
		rifleGift->setLife(true); //Mark the gift as collected.
		return;
	}
	else
	{
		std::cout << "Player-RifleGift collision not handled properly!" << std::endl;
		return;
	}
}

//------------------------------------------------------------------------------
void handlePlayerMachineGunGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Player* player = nullptr;
	MachineGunGift* machineGunGift = nullptr;

	//Handle Player vs Machine-Gun Gift collision (bidirectional)
	if (auto* tempPlayer = dynamic_cast<Player*>(&obj1))
	{
		if (auto* tempMachineGunGift = dynamic_cast<MachineGunGift*>(&obj2))
		{
			player = tempPlayer;
			machineGunGift = tempMachineGunGift;
		}
	}
	//Handle Machine-Gun Gift vs Player collision (reverse direction)
	if (auto* tempMachineGunGift = dynamic_cast<MachineGunGift*>(&obj1))
	{
		if (auto* tempPlayer = dynamic_cast<Player*>(&obj2))
		{
			player = tempPlayer;
			machineGunGift = tempMachineGunGift;
		}
	}

	if (player && machineGunGift)
	{
		player->changeSpriteAnimation(PLAYER_MACHINE_GUN);
		machineGunGift->setLife(true); //Mark the gift as collected.
		return;
	}
	else
	{
		std::cout << "Player-MachineGunGift collision not handled properly!" << std::endl;
		return;
	}
}

//------------------------------------------------------------------------------
void handlePlayerBazookaGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Player* player = nullptr;
	BazookaGift* bazookaGift = nullptr;

	//Handle Player vs Bazooka Gift collision (bidirectional)
	if (auto* tempPlayer = dynamic_cast<Player*>(&obj1)) 
	{
		if (auto* tempBazookaGift = dynamic_cast<BazookaGift*>(&obj2)) 
		{
			player = tempPlayer;
			bazookaGift = tempBazookaGift;
		}
	}
	//Handle Bazooka Gift vs Player collision (reverse direction)
	if (auto* tempBazookaGift = dynamic_cast<BazookaGift*>(&obj1))
	{
		if (auto* tempPlayer = dynamic_cast<Player*>(&obj2))
		{
			player = tempPlayer;
			bazookaGift = tempBazookaGift;
		}
	}

	if (player && bazookaGift) 
	{
		player->changeSpriteAnimation(PLAYER_BAZOOKA);
		bazookaGift->setLife(true); //Mark the gift as collected.
		return;
	}
	else
	{
		std::cout << "Player-BazookaGift collision not handled properly!" << std::endl;
		return;
	}
}

//------------------------------------------------------------------------------
static bool g_playerCollisionRegistered = []() {
	auto& factory = CollisionFactory::getInstance();
	factory.registerTypedCollision<Player, Enemy>(handlePlayerEnemyCollision);
	factory.registerTypedCollision<Player, Wall>(handlePlayerWallCollision);
	factory.registerTypedCollision<Player, Obstacles>(handlePlayerObstaclesCollision);
	factory.registerTypedCollision<Player, Explosion>(handlePlayerExplosionCollision);
	factory.registerTypedCollision<Player, RifleGift>(handlePlayerRifleGiftCollision);
	factory.registerTypedCollision<Player, MachineGunGift>(handlePlayerMachineGunGiftCollision);
	factory.registerTypedCollision<Player, BazookaGift>(handlePlayerRifleGiftCollision);
	return true;
	}();
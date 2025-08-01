//-----include section-----
#include "Player.h"
#include "CollisionFactory.h"
#include "Factory.h"
#include <OneDirectionAttackBehavior.h>
#include <AllDirectionsAttackBehavior.h>
#include "Enemy.h"
#include "Wall.h"
#include "GamePlay.h"

//-----functions section------
//-----------------------------------------------------------------------------
Player::Player()
	: UpdateableObject(), m_lives(NUM_OF_LIVES), m_bulletCount(NUM_OF_BULLETS), 
      m_bombsCount(NUM_OF_BOMBS), m_bKeyPressed(false)
{}

//-----------------------------------------------------------------------------
void Player::initialization(sf::Vector2f position, std::string name, GamePlay* gamePlay)
{
	auto& texture = ResourcesManager::getInstance().getTexture(name);
	m_pic.setTexture(texture);
	m_numberOfFrames = m_pic.getTexture()->getSize().x / OBJECT_WIDTH; //Calculate number of frames based on texture width.
	m_pic.setRotation(180.f); //Set initial rotation to face down.
	set_frames(m_numberOfFrames, position, OBJECT_WIDTH, OBJECT_HEIGHT);

	setCurrentWeapon(RIFLE_NAME); //Set default weapon to Rifle.
	setShootCooldown(RIFLE_NAME); //Set the shoot cooldown based on the weapon name.

	m_attackBehavior = std::move(std::make_unique<OneDirectionAttackBehavior>());
	m_lives = NUM_OF_LIVES;

	m_gamePlay = gamePlay;

	m_bulletCount = NUM_OF_BULLETS;
	m_bombsCount = NUM_OF_BOMBS;
	m_bKeyPressed = false;
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
		m_direction = DEFAULT_VECTOR;
		this->setRotation(m_direction);
		return;
	}

	sf::Vector2f newDir(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) newDir.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) newDir.x += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) newDir.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) newDir.y += 1.f;

	//Normalize direction if moving diagonally.
	if (newDir != DEFAULT_VECTOR)
	{
		newDir /= std::sqrt(newDir.x * newDir.x + newDir.y * newDir.y);
    
		m_facingDirection = newDir; //Update facing direction when moving.
		this->setRotation(m_facingDirection);
	}

	m_direction = newDir;
}

//------------------------------------------------------------------------------
void Player::setShootCooldown(const std::string& weaponName)
{
	for (const auto& pair : m_shootCooldowns)
	{
		if (pair.first == weaponName)
		{
			m_shootCooldown = pair.second;
			return;
		}
	}

	std::cerr << "Weapon name not found in cooldowns: " << weaponName << std::endl;
	m_shootCooldown = sf::seconds(0.25); //Default cooldown if not found.
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
	m_gamePlay->playHitSound();
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
	if (m_lives > NUM_OF_LIVES) m_lives = NUM_OF_LIVES;
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
	m_bulletCount--;
}

//-----------------------------------------------------------------------------
bool Player::isBulletsAvailable()
{
	if (m_bulletCount > MIN_BOUND_BULLETS)
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
bool Player::isBombsAvailable()
{
	if (m_bombsCount > MIN_BOUND_BOMBS)
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (m_shootClock.getElapsedTime() >= m_shootCooldown && isBulletsAvailable())
		{
			m_gamePlay->addProjectile(this->getPosition(), 
									  m_attackBehavior->Attack(m_facingDirection), 
									  _PLAYER,
									  getCurrentWeaponName());
			decBullets();
			m_shootClock.restart(); //Reset timer.
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		if (!m_bKeyPressed && isBombsAvailable()) //Only create bomb on first press.
		{
			m_gamePlay->addBomb(this->getPosition());
			m_bKeyPressed = true;
			m_bombsCount--;
		}
	}
	else
	{
		m_bKeyPressed = false; //Reset when key is released.
	}
}

//-----------------------------------------------------------------------------
void Player::setAttackBehavior(std::unique_ptr<AttackBehavior> attackBehavior)
{
	m_attackBehavior = std::move(attackBehavior);
}

//------------------------------------------------------------------------------
void Player::presentSound()
{
	m_gamePlay->playPresentSound();
}

//------------------------------------------------------------------------------
void Player::medkitSound()
{
	m_gamePlay->playMedkitSound();
}

//------------------------------------------------------------------------------
void Player::removeEnemyGift()
{
	m_gamePlay->removeEnemy();
}

//------------------------------------------------------------------------------
void Player::removeTimeGift()
{
	m_gamePlay->decTime();
}

//------------------------------------------------------------------------------
int Player::getNumOfBombs() const
{
	return m_bombsCount;
}

//------------------------------------------------------------------------------
std::string Player::getCurrentWeaponName() const
{
	return m_currentWeapon;
}

//------------------------------------------------------------------------------
void Player::setCurrentWeapon(const std::string& weapon)
{
	m_currentWeapon = weapon;
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
		//don't do anything if the player hit the enemy.
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
}

//------------------------------------------------------------------------------
void handlePlayerObstaclesCollision(GameObject& obj1, GameObject& obj2)
{
	Player* player = nullptr;
	Obstacles* obstacle = nullptr;

	//Handle Player vs Wall collision (bidirectional)
	if (auto* tempPlayer = dynamic_cast<Player*>(&obj1))
	{
		if (auto* tempObstacle = dynamic_cast<Obstacles*>(&obj2))
		{
			player = tempPlayer;
			obstacle = tempObstacle;
		}
	}
	//Handle Wall vs Player collision (reverse direction)
	if (auto* tempObstacle = dynamic_cast<Obstacles*>(&obj1))
	{
		if (auto* tempPlayer = dynamic_cast<Player*>(&obj2))
		{
			player = tempPlayer;
			obstacle = tempObstacle;
		}
	}

	if (player && obstacle)
	{
		player->setPosition(player->getPrevLocation());
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
		player->presentSound();
		player->changeSpriteAnimation(PLAYER_RIFLE, OBJECT_WIDTH, OBJECT_HEIGHT);
		player->setCurrentWeapon(RIFLE_NAME); //Set the current weapon to rifle.
		player->setShootCooldown(RIFLE_NAME); //Set the shoot cooldown for rifle.
		rifleGift->setLife(true); //Mark the gift as collected.
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
		player->presentSound();
		player->changeSpriteAnimation(PLAYER_MACHINE_GUN, OBJECT_WIDTH, OBJECT_HEIGHT);
		player->setCurrentWeapon(MACHINE_GUN_NAME); //Set the current weapon to machine-gun.
		player->setShootCooldown(MACHINE_GUN_NAME); //Set the shoot cooldown for machine-gun.
		machineGunGift->setLife(true); //Mark the gift as collected.
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
		player->presentSound();
		player->changeSpriteAnimation(PLAYER_BAZOOKA, OBJECT_WIDTH, OBJECT_HEIGHT);
		player->setCurrentWeapon(BAZOOKA_NAME); //Set the current weapon to bazooka.
		player->setShootCooldown(BAZOOKA_NAME); //Set the shoot cooldown for bazooka.
		bazookaGift->setLife(true); //Mark the gift as collected.
		return;
	}
}

//------------------------------------------------------------------------------
void handlePlayerBulletsGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Player* player = nullptr;
	BulletsGift* bullentsGift = nullptr;

	//Handle Player vs Bazooka Gift collision (bidirectional)
	if (auto* tempPlayer = dynamic_cast<Player*>(&obj1))
	{
		if (auto* tempBullentsGift = dynamic_cast<BulletsGift*>(&obj2))
		{
			player = tempPlayer;
			bullentsGift = tempBullentsGift;
		}
	}
	//Handle Bazooka Gift vs Player collision (reverse direction)
	if (auto* tempBullentsGift = dynamic_cast<BulletsGift*>(&obj1))
	{
		if (auto* tempPlayer = dynamic_cast<Player*>(&obj2))
		{
			player = tempPlayer;
			bullentsGift = tempBullentsGift;
		}
	}

	if (player && bullentsGift)
	{
		player->presentSound();
		player->addBullets(NUM_OF_BULLETS);
		bullentsGift->setLife(true); //Mark the gift as collected.
		return;
	}
}

//------------------------------------------------------------------------------
void handlePlayerMedkitGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Player* player = nullptr;
	MedkitGift* medkitGift = nullptr;

	//Handle Player vs Bazooka Gift collision (bidirectional)
	if (auto* tempPlayer = dynamic_cast<Player*>(&obj1))
	{
		if (auto* tempMedkitsGift = dynamic_cast<MedkitGift*>(&obj2))
		{
			player = tempPlayer;
			medkitGift = tempMedkitsGift;
		}
	}
	//Handle Bazooka Gift vs Player collision (reverse direction)
	if (auto* tempMedkitsGift = dynamic_cast<MedkitGift*>(&obj1))
	{
		if (auto* tempPlayer = dynamic_cast<Player*>(&obj2))
		{
			player = tempPlayer;
			medkitGift = tempMedkitsGift;
		}
	}

	if (player && medkitGift)
	{
		player->medkitSound();
		player->incLife(ADD_LIFE);
		medkitGift->setLife(true); //Mark the gift as collected.
		return;
	}
}

//------------------------------------------------------------------------------
void handlePlayerRemoveTimeGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Player* player = nullptr;
	RemoveTime* RemoveTimeGift = nullptr;

	if (auto* tempPlayer = dynamic_cast<Player*>(&obj1))
	{
		if (auto* tempRemoveTimeGift = dynamic_cast<RemoveTime*>(&obj2))
		{
			player = tempPlayer;
			RemoveTimeGift = tempRemoveTimeGift;
		}
	}

	if (auto* tempRemoveTimeGift = dynamic_cast<RemoveTime*>(&obj1))
	{
		if (auto* tempPlayer = dynamic_cast<Player*>(&obj2))
		{
			player = tempPlayer;
			RemoveTimeGift = tempRemoveTimeGift;
		}
	}

	if (player && RemoveTimeGift)
	{
		player->presentSound();
		player->removeTimeGift();
		RemoveTimeGift->setLife(true); 
		return;
	}
}

//------------------------------------------------------------------------------
void handlePlayerRemoveEnemyGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Player* player = nullptr;
	RemoveEnemy* RemoveEnemyGift = nullptr;

	if (auto* tempPlayer = dynamic_cast<Player*>(&obj1))
	{
		if (auto* tempRemoveEnemyGift = dynamic_cast<RemoveEnemy*>(&obj2))
		{
			player = tempPlayer;
			RemoveEnemyGift = tempRemoveEnemyGift;
		}
	}

	if (auto* tempRemoveEnemyGift = dynamic_cast<RemoveEnemy*>(&obj1))
	{
		if (auto* tempPlayer = dynamic_cast<Player*>(&obj2))
		{
			player = tempPlayer;
			RemoveEnemyGift = tempRemoveEnemyGift;
		}
	}

	if (player && RemoveEnemyGift)
	{
		player->presentSound();
		player->removeEnemyGift();
		RemoveEnemyGift->setLife(true); 
		return;
	}
}

//------------------------------------------------------------------------------
static bool g_playerCollisionRegistered = []() {
	auto& factory = CollisionFactory::getInstance();
	factory.registerTypedCollision<Player, Enemy>(handlePlayerEnemyCollision);
	factory.registerTypedCollision<Player, Wall>(handlePlayerWallCollision);
	factory.registerTypedCollision<Player, Obstacles>(handlePlayerObstaclesCollision);
	factory.registerTypedCollision<Player, RifleGift>(handlePlayerRifleGiftCollision);
	factory.registerTypedCollision<Player, MachineGunGift>(handlePlayerMachineGunGiftCollision);
	factory.registerTypedCollision<Player, BazookaGift>(handlePlayerBazookaGiftCollision);
	factory.registerTypedCollision<Player, BulletsGift>(handlePlayerBulletsGiftCollision);
	factory.registerTypedCollision<Player, MedkitGift>(handlePlayerMedkitGiftCollision);
	factory.registerTypedCollision<Player, RemoveTime>(handlePlayerRemoveTimeGiftCollision);
	factory.registerTypedCollision<Player, RemoveEnemy>(handlePlayerRemoveEnemyGiftCollision);
	return true;
	}();
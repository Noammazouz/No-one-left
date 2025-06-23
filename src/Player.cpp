//-----include section-----
#include "Player.h"
#include "Factory.h"

//-----functions section------
//-----------------------------------------------------------------------------
//Defines the static members.
int Player::m_score = 0;

//-----------------------------------------------------------------------------
Player::Player()
	: UpdateableObject()
{}

//-----------------------------------------------------------------------------
Player::Player(sf::Vector2f position, std::string name)
	: UpdateableObject(position, name), m_lives(NUM_OF_LIVES)
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

//------------------------------------------------------------------------------
//Register player handle collisions.
//void Player::registerPlayerCollisions()
//{
//	static bool registered = false;
//	if (registered) return;
//
//	auto& collisionFactory = CollisionFactory::getInstance();
//
//	// Register player-enemy collisions
//	collisionFactory.registerTypedCollision<Player, Enemy>(handlePlayerEnemyCollision);
//	// Register player-wall collisions
//	collisionFactory.registerTypedCollision<Player, Wall>(handlePlayerWallCollision);
//
//	registered = true;
//	std::cout << "Player collisions registered." << std::endl;
//}
//
////------------------------------------------------------------------------------
////Auto-registration helper - runs when the player is created.
//static bool g_playerCollisionRegistered = []()
//	{
//		Player::registerPlayerCollisions();
//		return true;
//	}();
//
////------------------------------------------------------------------------------
//void handlePlayerEnemyCollision(GameObject& obj1, GameObject& obj2)
//{
//	if (auto* player = dynamic_cast<Player*>(&obj1))
//	{
//		if (auto* enemy = dynamic_cast<Enemy*>(&obj2))
//		{
//			std::cout << "Player collided with enemy - Player loses a life!" << std::endl;
//			player->decLife();
//			if (player->getLife() <= 0)
//			{
//				std::cout << "Player has no lives left - Game Over!" << std::endl;
//				player->setWin(false); //Set win to false if player has no lives left.
//			}
//		}
//	}
//	else if (auto* player = dynamic_cast<Player*>(&obj2))
//	{
//		if (auto* enemy = dynamic_cast<Enemy*>(&obj1))
//		{
//			std::cout << "Player collided with enemy - Player loses a life!" << std::endl;
//			player->decLife();
//			if (player->getLife() <= 0)
//			{
//				std::cout << "Player has no lives left - Game Over!" << std::endl;
//				player->setWin(false); //Set win to false if player has no lives left.
//			}
//		}
//	}
//}
//
////------------------------------------------------------------------------------
//void handlePlayerWallCollision(GameObject& obj1, GameObject& obj2)
//{
//	if (auto* player = dynamic_cast<Player*>(&obj1))
//	{
//		std::cout << "Player collided with wall - Stopping movement!" << std::endl;
//		player->setPosition(player->getPrevLocation()); //Reset position to previous location.
//	}
//	else if (auto* player = dynamic_cast<Player*>(&obj2))
//	{
//		std::cout << "Player collided with wall - Stopping movement!" << std::endl;
//		player->setPosition(player->getPrevLocation()); //Reset position to previous location.
//	}
//}
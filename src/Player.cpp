//-----include section-----
#include "Player.h"

//-----functions section------
//-----------------------------------------------------------------------------
//Defines the static members.
int Player::m_lives = NUM_OF_LIVES;
int Player::m_score = 0;

//-----------------------------------------------------------------------------
Player::Player()
	: UpdateableObject()
{
	/*m_pic.setSize(sf::Vector2f(50.f, 50.f));
	m_pic.setPosition(sf::Vector2f(500.f, 500.f));
	m_pic.setOutlineThickness(5.f);
	m_pic.setFillColor(sf::Color::Black);

    m_pic.setOrigin(m_pic.getSize().x / 2.f, m_pic.getSize().y / 2.f);*/
}

//-----------------------------------------------------------------------------
Player::Player(sf::Vector2f position, const sf::Texture& texture)
	: UpdateableObject(sf::Vector2f(100.f, 100.f), texture)
{}

//-----------------------------------------------------------------------------
void Player::update(sf::Time deltaTime)
{
	this->setPrevLocation(this->getPosition());
	this->updatePosition(m_direction * PLAYER_SPEED * deltaTime.asSeconds());
	//m_pic.move(m_direction * PLAYER_SPEED * deltaTime.asSeconds());
}

//-----------------------------------------------------------------------------
void Player::setDirection(sf::Vector2f position)
{
	if (checkDirection())
	{
		// Get the current key being pressed and update movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			m_direction = sf::Vector2f(-1, 0);
			this->mirrorImage(m_direction);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			m_direction = sf::Vector2f(1, 0);
			this->mirrorImage(m_direction);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			m_direction = sf::Vector2f(0, -1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			m_direction = sf::Vector2f(0, 1);
		}

		//this->setRotation(m_direction);
	}
	else
	{
		// If no movement keys are pressed, stop the player
		m_direction = sf::Vector2f(0, 0);
	}

	this->setRotation(m_direction);
}

//void Player::setDirection(sf::Vector2f position)
//{
//	static sf::Clock rotationClock; // Clock persists across calls
//	float deltaTime = rotationClock.restart().asSeconds();
//
//	const auto right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
//	const auto left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
//	const auto up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
//	const auto down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
//
//	if (checkDeriction())
//	{
//		if (left)
//		{
//			m_direction = sf::Vector2f(-1, 0);
//			m_targetAngle = 270.f;
//		}
//		else if (right)
//		{
//			m_direction = sf::Vector2f(1, 0);
//			m_targetAngle = 90.f;
//		}
//		else if (up)
//		{
//			m_direction = sf::Vector2f(0, -1);
//			m_targetAngle = 0.f;
//		}
//		else if (down)
//		{
//			m_direction = sf::Vector2f(0, 1);
//			m_targetAngle = 180.f;
//		}
//		//else if (up && right)
//		//{
//		//	m_direction = sf::Vector2f(0, -0.5f);
//		//	m_targetAngle = 45.f; // Maintain current angle
//		//}
//	}
//	else
//	{
//		m_direction = sf::Vector2f(0, 0);
//	}
//
//	// --- Smooth rotation towards m_targetAngle ---
//	float currentAngle = m_pic.getRotation();
//
//	// Normalize angle difference to [-180, 180]
//	float deltaAngle = std::fmod(m_targetAngle - currentAngle + 540.f, 360.f) - 180.f;
//
//	// Compute step
//	float rotationStep = ROTATION_SPEED * deltaTime;
//
//	// Apply smooth turn
//	if (std::abs(deltaAngle) < rotationStep)
//		currentAngle = m_targetAngle;
//	else
//		currentAngle += (deltaAngle > 0 ? 1 : -1) * rotationStep;
//
//	m_pic.setRotation(currentAngle);
//}

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
	return getObjPosition();
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
//void Player::draw(sf::RenderWindow& window)
//{
//	// Draw the player rectangle
//	//window.draw(m_pic);
//}

//------------------------------------------------------------------------------

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
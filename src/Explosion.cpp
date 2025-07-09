#include "Explosion.h"
#include "ResourcesManager.h"
#include "GamePlay.h"
#include "CollisionFactory.h"
#include "Enemy.h"
#include "Wall.h"
#include "Player.h"


Explosion::Explosion(sf::Vector2f position)
	:UpdateableObject(position, EXPLOSION_NAME)
{
    m_numberOfFrames = m_pic.getTexture()->getSize().x / EXPLOSION_WIDTH;
    set_frames(m_numberOfFrames, position, EXPLOSION_WIDTH, EXPLOSION_HEIGHT);

}

void Explosion::update(sf::Time deltaTime, sf::Vector2f /*playerPos*/)
{
    m_timer -= deltaTime;
    updateFrames(DEFAULT_DIRECTION, EXPLOSION_FRAME_TIME, m_numberOfFrames);
    if (m_timer <= sf::Time::Zero)
    {
        this->setLife(true);
    }
}

void handleExplosionEnemyCollision(GameObject& obj1, GameObject& obj2)
{
    Explosion* expoPtr = nullptr;
    Enemy* enemyPtr = nullptr;
    if (auto* expo = dynamic_cast<Explosion*>(&obj1))
    {
        if (auto* enemy = dynamic_cast<Enemy*>(&obj2))
        {
            expoPtr = expo;
            enemyPtr = enemy;
        }
    }
    else if (auto* expo1 = dynamic_cast<Explosion*>(&obj2))
    {
        if (auto* enemy = dynamic_cast<Enemy*>(&obj1))
        {
            expoPtr = expo1;
            enemyPtr = enemy;
        }
    }
    if (expoPtr && enemyPtr)
    {
        enemyPtr->setLife(true);  // or enemy->decLife()
    }
}

void handleExplosionPlayerCollision(GameObject& obj1, GameObject& obj2)
{
    Explosion* expoPtr = nullptr;
    Player* playerPtr = nullptr;
    if (auto* expo = dynamic_cast<Explosion*>(&obj1))
    {
        if (auto* player = dynamic_cast<Player*>(&obj2))
        {
            expoPtr = expo;
            playerPtr = player;
        }
    }
    else if (auto* expo = dynamic_cast<Explosion*>(&obj2))
    {
        if (auto* player = dynamic_cast<Player*>(&obj1))
        {
            expoPtr = expo;
            playerPtr = player;
        }
    }
    if (expoPtr && playerPtr)
    {
        playerPtr->decLife(EXPLOSION_DAMAGE);  // you can define EXPLOSION_DAMAGE as a const
    }
}

void handleExplosionObstacleCollision(GameObject& obj1, GameObject& obj2)
{
    Explosion* expoPtr = nullptr;
    Obstacles* ObstPtr = nullptr;
    if (auto* expo = dynamic_cast<Explosion*>(&obj1))
    {
        if (auto* Obst = dynamic_cast<Obstacles*>(&obj2))
        {
            expoPtr = expo;
            ObstPtr = Obst;
        }
    }
    else if (auto* expo = dynamic_cast<Explosion*>(&obj2))
    {
        if (auto* Obst = dynamic_cast<Obstacles*>(&obj1))
        {
            expoPtr = expo;
            ObstPtr = Obst;
        }
    }
    if (expoPtr && ObstPtr)
    {
        ObstPtr->setLife(true);  // if obstacle has lives
    }
}

void handleExplosionRifleGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Explosion* expoPtr = nullptr;
	RifleGift* rifleGift = nullptr;

	//Handle Player vs Rifle Gift collision (bidirectional)
	if (auto* expo = dynamic_cast<Explosion*>(&obj1))
	{
		if (auto* tempRifleGift = dynamic_cast<RifleGift*>(&obj2))
		{
			expoPtr = expo;
			rifleGift = tempRifleGift;
		}
	}
	//Handle Rifle Gift vs Player collision (reverse direction)
	if (auto* tempRifleGift = dynamic_cast<RifleGift*>(&obj1))
	{
		if (auto* expo = dynamic_cast<Explosion*>(&obj2))
		{
			expoPtr = expo;
			rifleGift = tempRifleGift;
		}
	}

	if (expoPtr && rifleGift)
	{
		rifleGift->setLife(true); //Mark the gift as collected.
		return;
	}
}

//------------------------------------------------------------------------------
void handleExplosionMachineGunGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Explosion* expoPtr = nullptr;
	MachineGunGift* machineGunGift = nullptr;

	//Handle Player vs Machine-Gun Gift collision (bidirectional)
	if (auto* expo = dynamic_cast<Explosion*>(&obj1))
	{
		if (auto* tempMachineGunGift = dynamic_cast<MachineGunGift*>(&obj2))
		{
			expoPtr = expo;
			machineGunGift = tempMachineGunGift;
		}
	}
	//Handle Machine-Gun Gift vs Player collision (reverse direction)
	if (auto* tempMachineGunGift = dynamic_cast<MachineGunGift*>(&obj1))
	{
		if (auto* expo = dynamic_cast<Explosion*>(&obj2))
		{
			expoPtr = expo;
			machineGunGift = tempMachineGunGift;
		}
	}

	if (expoPtr && machineGunGift)
	{
		machineGunGift->setLife(true); //Mark the gift as collected.
		return;
	}
}

//------------------------------------------------------------------------------
void handleExplosionBazookaGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Explosion* expoPtr = nullptr;
	BazookaGift* bazookaGift = nullptr;

	//Handle Player vs Bazooka Gift collision (bidirectional)
	if (auto* expo = dynamic_cast<Explosion*>(&obj1))
	{
		if (auto* tempBazookaGift = dynamic_cast<BazookaGift*>(&obj2))
		{
			expoPtr = expo;
			bazookaGift = tempBazookaGift;
		}
	}
	//Handle Bazooka Gift vs Player collision (reverse direction)
	if (auto* tempBazookaGift = dynamic_cast<BazookaGift*>(&obj1))
	{
		if (auto* expo = dynamic_cast<Explosion*>(&obj2))
		{
			expoPtr = expo;
			bazookaGift = tempBazookaGift;
		}
	}

	if (expoPtr && bazookaGift)
	{
		bazookaGift->setLife(true); //Mark the gift as collected.
		return;
	}
}

//------------------------------------------------------------------------------
void handleExplosionBulletsGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Explosion* expoPtr = nullptr;
	BulletsGift* bullentsGift = nullptr;

	//Handle Player vs Bazooka Gift collision (bidirectional)
	if (auto* expo = dynamic_cast<Explosion*>(&obj1))
	{
		if (auto* tempBullentsGift = dynamic_cast<BulletsGift*>(&obj2))
		{
			expoPtr = expo;
			bullentsGift = tempBullentsGift;
		}
	}
	//Handle Bazooka Gift vs Player collision (reverse direction)
	if (auto* tempBullentsGift = dynamic_cast<BulletsGift*>(&obj1))
	{
		if (auto* expo = dynamic_cast<Explosion*>(&obj2))
		{
			expoPtr = expo;
			bullentsGift = tempBullentsGift;
		}
	}

	if (expoPtr && bullentsGift)
	{
		bullentsGift->setLife(true); //Mark the gift as collected.
		return;
	}
}

//------------------------------------------------------------------------------
void handleExplosionMedkitGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Explosion* expoPtr = nullptr;
	MedkitGift* medkitGift = nullptr;

	//Handle Player vs Bazooka Gift collision (bidirectional)
	if (auto* expo = dynamic_cast<Explosion*>(&obj1))
	{
		if (auto* tempMedkitsGift = dynamic_cast<MedkitGift*>(&obj2))
		{
			expoPtr = expo;
			medkitGift = tempMedkitsGift;
		}
	}
	//Handle Bazooka Gift vs Player collision (reverse direction)
	if (auto* tempMedkitsGift = dynamic_cast<MedkitGift*>(&obj1))
	{
		if (auto* expo = dynamic_cast<Explosion*>(&obj2))
		{
			expoPtr = expo;
			medkitGift = tempMedkitsGift;
		}
	}

	if (expoPtr && medkitGift)
	{
		medkitGift->setLife(true); //Mark the gift as collected.
		return;
	}
}

//------------------------------------------------------------------------------
void handleExplosionRemoveTimeGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Explosion* expoPtr = nullptr;
	RemoveTime* RemoveTimeGift = nullptr;

	if (auto* expo = dynamic_cast<Explosion*>(&obj1))
	{
		if (auto* tempRemoveTimeGift = dynamic_cast<RemoveTime*>(&obj2))
		{
			expoPtr = expo;
			RemoveTimeGift = tempRemoveTimeGift;
		}
	}

	if (auto* tempRemoveTimeGift = dynamic_cast<RemoveTime*>(&obj1))
	{
		if (auto* expo = dynamic_cast<Explosion*>(&obj2))
		{
			expoPtr = expo;
			RemoveTimeGift = tempRemoveTimeGift;
		}
	}

	if (expoPtr && RemoveTimeGift)
	{
		RemoveTimeGift->setLife(true);
		return;
	}
}

//------------------------------------------------------------------------------
void handleExplosionRemoveEnemyGiftCollision(GameObject& obj1, GameObject& obj2)
{
	Explosion* expoPtr = nullptr;
	RemoveEnemy* RemoveEnemyGift = nullptr;

	if (auto* expo = dynamic_cast<Explosion*>(&obj1))
	{
		if (auto* tempRemoveEnemyGift = dynamic_cast<RemoveEnemy*>(&obj2))
		{
			expoPtr = expo;
			RemoveEnemyGift = tempRemoveEnemyGift;
		}
	}

	if (auto* tempRemoveEnemyGift = dynamic_cast<RemoveEnemy*>(&obj1))
	{
		if (auto* expo = dynamic_cast<Explosion*>(&obj2))
		{
			expoPtr = expo;
			RemoveEnemyGift = tempRemoveEnemyGift;
		}
	}

	if (expoPtr && RemoveEnemyGift)
	{
		RemoveEnemyGift->setLife(true);
		return;
	}
}

//-----------------------------------------------------------------------------
//Collision handler for Bullet vs Wall - Order independent.
void handleExplosionWallCollision(GameObject& obj1, GameObject& obj2)
{
	Explosion* expoPtr = nullptr;
	Wall* wallPtr = nullptr;

	//Check both parameter orders.
	if (auto* explosion = dynamic_cast<Explosion*>(&obj1))
	{
		if (auto* wall = dynamic_cast<Wall*>(&obj2))
		{
			expoPtr = explosion;
			wallPtr = wall;
		}

	}
	else if (auto* explosion1 = dynamic_cast<Explosion*>(&obj2))
	{
		if (auto* wall = dynamic_cast<Wall*>(&obj1))
		{
			wallPtr = wall;
			expoPtr = explosion1;
		}

	}

	if (expoPtr && wallPtr)
	{
		wallPtr->setLife(true);
	}
}

void Explosion::registerExplosionCollisions()
{
    static bool registered = false;
    if (registered) return;

    auto& factory = CollisionFactory::getInstance();
    factory.registerTypedCollision<Explosion, Enemy>(handleExplosionEnemyCollision);
    factory.registerTypedCollision<Explosion, Player>(handleExplosionPlayerCollision);
    factory.registerTypedCollision<Explosion, Obstacles>(handleExplosionObstacleCollision);
    factory.registerTypedCollision<Explosion, RifleGift>(handleExplosionRifleGiftCollision);
    factory.registerTypedCollision<Explosion, MachineGunGift>(handleExplosionMachineGunGiftCollision);
    factory.registerTypedCollision<Explosion, BazookaGift>(handleExplosionBazookaGiftCollision);
    factory.registerTypedCollision<Explosion, BulletsGift>(handleExplosionBulletsGiftCollision);
    factory.registerTypedCollision<Explosion, MedkitGift>(handleExplosionMedkitGiftCollision);
    factory.registerTypedCollision<Explosion, RemoveTime>(handleExplosionRemoveTimeGiftCollision);
    factory.registerTypedCollision<Explosion, RemoveEnemy>(handleExplosionRemoveEnemyGiftCollision);
    factory.registerTypedCollision<Explosion, Wall>(handleExplosionWallCollision);

    

    registered = true;
}


bool g_explosionCollisionRegistered = []()
    {
        Explosion::registerExplosionCollisions();
        return true;
    }();
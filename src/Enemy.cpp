#include "Enemy.h"
#include "Factory.h"

Enemy::Enemy(sf::Vector2f position, const sf::Texture& texture)
	: UpdateableObject(position, texture), m_direction(0, 0), m_prevlocation(position)
{
}

bool Enemy::registerEnemy(ObjectType type)
{
    // We register with Factory<UpdateableObject> so the factory returns
    // a unique_ptr<UpdateableObject> that actually points to an Enemy.
    return Factory<UpdateableObject>::instance()
        .registerType(
            type,
            // This lambda signature must match Factory<FuncType>:
            //   (const sf::Texture&, const sf::Vector2f&, float, float)
            [](const sf::Texture& texture,
                const sf::Vector2f& position,
                float width,
                float height) -> std::unique_ptr<UpdateableObject>
            {
                // Forward exactly those params into your Enemy constructor:
                return std::make_unique<Enemy>(position, texture);
            }
        );
}

// Then, trigger registration once at file scope:
static bool s_enemyRegistered = Enemy::registerEnemy(ObjectType::ENEMY);

void Enemy::update(sf::Time deltaTime)
{
	this->setPrevLocation(this->getPosition());
    this->updatePosition(m_direction * ENEMY_SPEED * deltaTime);
}

void Enemy::setDirection(sf::Vector2f playerPosition)
{
    m_prevlocation = this->getPosition();
	m_direction = pMoveBehavior_->Move(playerPosition, this->getPosition());
}
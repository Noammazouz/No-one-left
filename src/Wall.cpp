// Wall.cpp
#include "Wall.h"

Wall::Wall(const sf::Texture& texture, const sf::Vector2f& position, float width, float height)
	:StaticObject(texture, position, width, height)
{}


void Wall::collide(GameObject& otherObject)
{
    // for now, maybe do nothing or block movement
}

void Wall::explosionCollide(Explosion& otherobject)
{
    // what happens if an explosion hits a wall?
}

void Wall::enemyCollide(Enemy& otherObject)
{
    // what happens if an enemy runs into a wall?
}

void Wall::playerCollide(Player& otherObject)
{
    // what happens if the player runs into a wall?
}
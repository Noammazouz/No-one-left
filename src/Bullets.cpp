#include "Bullets.h"
//-----include section-----
#include "Bullets.h"
#include "Enemy.h"
#include "Player.h"
#include "Explosion.h"
#include "Wall.h"
#include "CollisionFactory.h"
#include <cmath>
#include <iostream>

//-----functions section------
//-----------------------------------------------------------------------------
Bullets::Bullets(std::string name, sf::Vector2f position)
    : ItemsToCollect("bullets", position)

{
}
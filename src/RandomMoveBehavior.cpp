//-----include section-----
#include "RandomMoveBehavior.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

//-----functions section------
//-----------------------------------------------------------------------------
RandomMoveBehavior::RandomMoveBehavior() 
{
    static bool initial = false;
    if (!initial) 
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        initial = true;
    }
    chooseNewDirection(); // choose first direction
}

void RandomMoveBehavior::Move(sf::Vector2f playerPos, float deltaTime)
{
    Timer += deltaTime;

    if (Timer >= CHANGE_DIRECTION_TIME) // change direction every 2 seconds
    {
        chooseNewDirection();
        Timer = 0;
    }

    enemyPos.x += direction.x * speed * deltaTime;
    enemyPos.y += direction.y * speed * deltaTime;
}

void RandomMoveBehavior::chooseNewDirection()
{
    int random_directon = rand() % 8;

    switch (random_directon)
    {
    case 0: direction = { 1, 0 };    break;  // right
    case 1: direction = { -1, 0 };   break;  // left
    case 2: direction = { 0, 1 };    break;  // down
    case 3: direction = { 0, -1 };   break;  // up
	case 4: direction = { 1, 1 };    break;  // right and down
    case 5: direction = { 1, -1 };   break;  // right and up
    case 6: direction = { -1, 1 };   break;  // left and down
    case 7: direction = { -1, -1 };  break;  // left and up
    }
}
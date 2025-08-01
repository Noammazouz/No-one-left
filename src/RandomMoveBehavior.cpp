//-----include section-----
#include "RandomMoveBehavior.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

//-----functions section------
//-----------------------------------------------------------------------------
RandomMoveBehavior::RandomMoveBehavior() 
    : m_timer(sf::seconds(RANDOM_MOVE_BEHAVIOR_TIME))
{
    static bool initial = false;
    if (!initial) 
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        initial = true;
    }
    chooseNewDirection(); // choose first direction
}

//-----------------------------------------------------------------------------
sf::Vector2f RandomMoveBehavior::Move(sf::Vector2f /*playerPos*/, sf::Time deltaTime, sf::Vector2f /*enemyPos*/)
{
    m_timer -= deltaTime;

    if (m_timer <= sf::Time::Zero) //change direction every 2 seconds
    {
        chooseNewDirection();
        m_timer = sf::seconds(RANDOM_MOVE_BEHAVIOR_TIME); //Reset timer
    }
    
    return m_direction;
}
//-----------------------------------------------------------------------------
void RandomMoveBehavior::OnCollision()
{
    m_timer = sf::seconds(2); //restart the interval
    chooseNewDirection();    //pick a fresh vector right now
}

//-----------------------------------------------------------------------------
void RandomMoveBehavior::chooseNewDirection()
{
    int random_direction = rand() % NUM_OF_DIRECTIONS;

    switch (random_direction)
    {
        case 0:
        {
            m_direction = { 1, 0 };
            break; //right
        }
        case 1:
        {
            m_direction = { -1, 0 };   
            break; //left
        }
        case 2:
        {
            m_direction = { 0, 1 };   
            break; //down
        }
        case 3:
        {
            m_direction = { 0, -1 };   
            break; //up
        }
        case 4:
        {
            m_direction = { 1, 1 };    
            break; //right and down
        }
        case 5:
        {
            m_direction = { 1, -1 };   
            break; //right and up
        }
        case 6:
        {
            m_direction = { -1, 1 };   
            break; //left and down
        }
        case 7:
        {
            m_direction = { -1, -1 };  
            break; // left and up
        }
    }
}
//-----include section-----
#include "AxisMoveBehavior.h"

//-----functions section------
//-----------------------------------------------------------------------------
void AxisMoveBehavior::Move(sf::Vector2f playerPos, float deltaTime)
 {
    Timer += deltaTime;

    if (Timer >= CHANGE_DIRECTION_TIME)
    {
        isMovingX = !isMovingX;
        Timer = 0;
    }

    float player_enemy_distance_x = playerPos.x - enemyPos.x;
    float player_enemy_distance_y = playerPos.y - enemyPos.y;

    sf::Vector2f moveDirection{ 0, 0 };

    if (isMovingX) 
    {
        if (player_enemy_distance_x > 0)
        {
            enemyPos.x -= speed * deltaTime; //player right, enemy left
        }
        else 
        {
            enemyPos.x += speed * deltaTime;  //player left, enemy right
        }
    }
    else
    {
        if (player_enemy_distance_y > 0)
        {
            enemyPos.y -= speed * deltaTime; //player down, enemy up
        }
        else
        {
            enemyPos.y += speed * deltaTime;  //player up, enemy down
        }
    }
}
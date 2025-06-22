#pragma once

//-----include section-----
#include "ItemsToCollect.h"
#include <SFML/Graphics.hpp>
#include "Const.h"

//-----class section-----
class Bullets : public ItemsToCollect
{
public:
    Bullets(sf::Vector2f position, sf::Vector2f dir = sf::Vector2f(1, 0), float spd = 300.0f);
    ~Bullets() = default;

    void update(float deltaTime);
    void setDirection(sf::Vector2f dir);
    void setSpeed(float spd);
    sf::Vector2f getDirection() const;
    float getSpeed() const;

    bool getIsActive() const;
    void setActive(bool active);
    bool isOutOfMap() const;

    /*virtual void collide(GameObject& otherObject) override;
    virtual void enemyCollide(Enemy& otherObject) override;
    virtual void playerCollide(Player& otherObject) override;
    virtual void explosionCollide(Explosion& otherobject) override;*/


private:
    sf::Vector2f direction;
    float speed;
    bool isActive;
};
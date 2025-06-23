//-----include section-----
#include "Bullets.h"


//-----functions section------
//-----------------------------------------------------------------------------
Bullets::Bullets(std::string name, const sf::Vector2f& position, BulletOwner owner)
    : ItemsToCollect(position, name), m_owner(owner)
{
}

//-----------------------------------------------------------------------------
BulletOwner Bullets::getOwner() const
{
    return m_owner;
}

//-----------------------------------------------------------------------------
void Bullets::setOwner(BulletOwner owner)
{
    m_owner = owner;
}



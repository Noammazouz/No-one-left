//-----include section-----
#include "CollisionFactory.h"

//-----Singleton Implementation-----
//-----------------------------------------------------------------------------
CollisionFactory& CollisionFactory::getInstance()
{
    static CollisionFactory instance;
    return instance;
}

//-----Factory Methods-----
//-----------------------------------------------------------------------------
void CollisionFactory::registerCollision(const std::type_index& type1, const std::type_index& type2, HitFunctionPtr handler)
{
    Key key = std::make_pair(type1, type2);
    m_collisionMap[key] = handler;
}

//-----------------------------------------------------------------------------
void CollisionFactory::processCollision(GameObject& object1, GameObject& object2)
{
    auto handler = lookup(typeid(object1), typeid(object2));
    if (handler)
    {
        handler(object1, object2);
    }
   
}

//-----Internal Methods-----
//-----------------------------------------------------------------------------
CollisionFactory::HitFunctionPtr CollisionFactory::lookup(const std::type_index& class1, const std::type_index& class2) const
{
    auto mapEntry = m_collisionMap.find(std::make_pair(class1, class2));
    if (mapEntry == m_collisionMap.end())
    {
        return nullptr;
    }
    return mapEntry->second;
}

//-----Utility Methods-----
//-----------------------------------------------------------------------------
bool CollisionFactory::hasCollisionHandler(const std::type_index& type1, const std::type_index& type2) const
{
    return m_collisionMap.find(std::make_pair(type1, type2)) != m_collisionMap.end();
}

//-----------------------------------------------------------------------------
void CollisionFactory::clearAllCollisions()
{
    m_collisionMap.clear();
}

//-----------------------------------------------------------------------------
size_t CollisionFactory::getRegisteredCollisionsCount() const
{
    return m_collisionMap.size();
} 
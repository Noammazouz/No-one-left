//-----include section-----
#include "RemoveEnemy.h"

//-----functions section------
//-----------------------------------------------------------------------------
RemoveEnemy::RemoveEnemy(const std::string& name, const sf::Vector2f& position)
    : ItemsToCollect(name, position)
{}

//-----------------------------------------------------------------------------
static bool RemoveEnemyGift = Factory<StaticObject>::instance().registerType(
    ObjectType::REMOVE_ENEMY,
    [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> {
        return std::make_unique<RemoveEnemy>(REMOVE_ENEMY_NAME, pos);
    });
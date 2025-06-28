//-----include section-----
#include "RemoveTime.h"


//-----functions section------
//-----------------------------------------------------------------------------
RemoveTime::RemoveTime(const std::string& name, const sf::Vector2f& position)
    : ItemsToCollect(name, position)
{
}

static bool RemoveTimeGift = Factory<StaticObject>::instance().registerType(
    ObjectType::REMOVE_TIME,
    [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> {
        return std::make_unique<RemoveTime>(REMOVE_TIME_NAME, pos);
    });
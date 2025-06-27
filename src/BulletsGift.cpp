//-----include section-----
#include "BulletsGift.h"
#include "Factory.h"

//-----functions section------
//-----------------------------------------------------------------------------
BulletsGift::BulletsGift(std::string name, const sf::Vector2f& position)
    : ItemsToCollect(name, position)
{}

//-----------------------------------------------------------------------------
static bool bulletsGift = Factory<StaticObject>::instance().registerType(
    ObjectType::BULLET,
    [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> {
        return std::make_unique<BulletsGift>(BULLETS_NAME, pos);
    });
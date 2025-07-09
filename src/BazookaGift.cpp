//-----include section-----
#include "BazookaGift.h"

//-----functions section------
//-----------------------------------------------------------------------------
BazookaGift::BazookaGift(const std::string& name, const sf::Vector2f& position)
	: WeaponsGift(name, position)
{}

//-----------------------------------------------------------------------------
static bool bazookaGift = Factory<StaticObject>::instance().registerType(
    ObjectType::BAZOOKA,
    [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> {
        return std::make_unique<BazookaGift>(BAZOOKA_NAME, pos);
    });
//-----include section-----
#include "RifleGift.h"

//-----functions section------
//-----------------------------------------------------------------------------
RifleGift::RifleGift(const std::string& name, const sf::Vector2f& position)
	: ItemsToCollect(name, position)
{}

static bool regObs1 = Factory<StaticObject>::instance().registerType(
    ObjectType::OBSTACLE1,
    [](const sf::Vector2f& pos, GamePlay* gamePlay) -> std::unique_ptr<StaticObject> {
        return std::make_unique<Obstacles>(pos, "obstacle1");
    });
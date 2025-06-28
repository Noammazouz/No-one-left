//-----include section-----
#include "RifleGift.h"
#include "Factory.h"

//-----functions section------
//-----------------------------------------------------------------------------
RifleGift::RifleGift(const std::string& name, const sf::Vector2f& position)
	: WeaponsGift(name, position)
{}

//-----------------------------------------------------------------------------
static bool rifleGift = Factory<StaticObject>::instance().registerType(
    ObjectType::RIFLE,
    [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> {
        return std::make_unique<RifleGift>(RIFLE_NAME, pos);
    });
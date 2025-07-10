//-----include section-----
#include "MedkitGift.h"

//-----functions section------
//-----------------------------------------------------------------------------
MedkitGift::MedkitGift(const std::string& name, const sf::Vector2f& position)
    : ItemsToCollect(name, position)
{
}

//-----------------------------------------------------------------------------
static bool medkitGift = Factory<StaticObject>::instance().registerType(
    ObjectType::MEDKIT,
    [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> {
        return std::make_unique<MedkitGift>(MED_KIT_NAME, pos);
    });
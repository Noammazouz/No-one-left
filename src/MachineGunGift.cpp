//-----include section-----
#include "MachineGunGift.h"

//-----functions section------
//-----------------------------------------------------------------------------
MachineGunGift::MachineGunGift(const std::string& name, const sf::Vector2f& position)
	: WeaponsGift(name, position)
{}

static bool machineGunGift = Factory<StaticObject>::instance().registerType(
    ObjectType::MACHINE_GUN,
    [](const sf::Vector2f& pos) -> std::unique_ptr<StaticObject> {
        return std::make_unique<MachineGunGift>(MACHINE_GUN_NAME, pos);
    });
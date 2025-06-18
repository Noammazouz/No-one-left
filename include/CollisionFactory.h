#pragma once

//-----include section-----
#include "GameObject.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

// Exception for unknown collisions
struct UnknownCollision : public std::runtime_error
{
    UnknownCollision(GameObject& a, GameObject& b)
        : std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
    {}
};

//-----class section-----
// Collision Factory Singleton Class
class CollisionFactory
{
public:
    // Singleton access
    static CollisionFactory& getInstance();

    // Function pointer type for collision handlers (same as multimethods approach)
    using HitFunctionPtr = void (*)(GameObject&, GameObject&);
    using Key = std::pair<std::type_index, std::type_index>;
    using HitMap = std::map<Key, HitFunctionPtr>;

    // Register collision handler (automatically symmetric)
    void registerCollision(const std::type_index& type1, const std::type_index& type2, HitFunctionPtr handler);
    
    // Template helper for type-safe registration
    template<typename T1, typename T2>
    void registerTypedCollision(void (*handler)(GameObject&, GameObject&));

    // Process collision (main factory method)
    void processCollision(GameObject& object1, GameObject& object2);

    // Utility methods
    bool hasCollisionHandler(const std::type_index& type1, const std::type_index& type2) const;
    void clearAllCollisions();
    size_t getRegisteredCollisionsCount() const;

private:
    // Singleton - private constructor/destructor
    CollisionFactory() = default;
    ~CollisionFactory() = default;
    CollisionFactory(const CollisionFactory&) = delete;
    CollisionFactory& operator=(const CollisionFactory&) = delete;

    // Internal methods
    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2) const;

    // Factory storage (same as multimethods approach)
    HitMap m_collisionMap;
};

//-----Template implementation-----
template<typename T1, typename T2>
void CollisionFactory::registerTypedCollision(void (*handler)(GameObject&, GameObject&))
{
    // Simple approach: just register the handler directly for both directions
    registerCollision(typeid(T1), typeid(T2), handler);
    registerCollision(typeid(T2), typeid(T1), handler);
} 
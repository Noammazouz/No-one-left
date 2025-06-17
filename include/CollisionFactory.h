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

    // Function pointer type for collision handlers
    using CollisionHandler = void (*)(GameObject&, GameObject&);
    using CollisionKey = std::pair<std::type_index, std::type_index>;

    // Template method for type-safe registration
    template<typename T1, typename T2>
    void registerTypedCollision(void (*handler)(T1&, T2&));

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
    CollisionHandler lookup(const std::type_index& class1, const std::type_index& class2) const;
    void registerCollisionInternal(const std::type_index& type1, const std::type_index& type2, CollisionHandler handler);

    // Factory storage
    std::map<CollisionKey, CollisionHandler> m_collisionMap;
};


//-----cpp section------
//This code is the template implementation.
//-----functions section------
//-----------------------------------------------------------------------------
template<typename T1, typename T2>
void CollisionFactory::registerTypedCollision(void (*handler)(T1&, T2&))
{
    // Create wrapper that does the casting automatically
    auto wrapper = [handler](GameObject& obj1, GameObject& obj2) {
        // Cast to the correct types (we know this is safe because of how we registered)
        if (typeid(obj1) == typeid(T1)) {
            // obj1 is T1, obj2 is T2
            T1& typed1 = static_cast<T1&>(obj1);
            T2& typed2 = static_cast<T2&>(obj2);
            handler(typed1, typed2);
        } else {
            // obj1 is T2, obj2 is T1 (symmetric)
            T1& typed1 = static_cast<T1&>(obj2);
            T2& typed2 = static_cast<T2&>(obj1);
            handler(typed1, typed2);
        }
    };

    // Register both directions
    registerCollisionInternal(typeid(T1), typeid(T2), wrapper);
    registerCollisionInternal(typeid(T2), typeid(T1), wrapper);
} 
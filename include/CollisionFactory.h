#pragma once

#include "GameObject.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <memory>

// Exception for unknown collisions
struct UnknownCollision : public std::runtime_error
{
    UnknownCollision(GameObject& a, GameObject& b)
        : std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
    {
    }
};

// Collision Factory Singleton Class
class CollisionFactory
{
public:
    // Singleton access
    static CollisionFactory& getInstance();

    // Function pointer type for collision handlers
    using CollisionHandler = std::function<void(GameObject&, GameObject&)>;
    using CollisionKey = std::pair<std::type_index, std::type_index>;

    // Factory methods
    template<typename T1, typename T2>
    void registerSymmetricCollision(CollisionHandler handler);

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

// Template implementations
template<typename T1, typename T2>
void CollisionFactory::registerSymmetricCollision(CollisionHandler handler)
{
    // Register both directions
    registerCollisionInternal(typeid(T1), typeid(T2), handler);
    
    // Create symmetric handler that swaps parameters
    auto symmetricHandler = [handler](GameObject& obj1, GameObject& obj2) {
        handler(obj2, obj1);
    };
    registerCollisionInternal(typeid(T2), typeid(T1), symmetricHandler);
} 
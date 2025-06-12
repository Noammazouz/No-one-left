#pragma once

#include "GameObject.h"
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <memory>

// Base interface for collision handlers
class ICollisionHandler
{
public:
    virtual ~ICollisionHandler() = default;
    virtual void handle(GameObject& object1, GameObject& object2) = 0;
};

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

    // Unique pointer type for collision handlers
    using CollisionKey = std::pair<std::type_index, std::type_index>;

    // Factory methods
    template<typename T1, typename T2>
    void registerSymmetricCollision(std::unique_ptr<ICollisionHandler> handler);

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
    ICollisionHandler* lookup(const std::type_index& class1, const std::type_index& class2) const;
    void registerCollisionInternal(const std::type_index& type1, const std::type_index& type2, std::unique_ptr<ICollisionHandler> handler);

    // Factory storage
    std::map<CollisionKey, std::unique_ptr<ICollisionHandler>> m_collisionMap;
};

// Template implementations
template<typename T1, typename T2>
void CollisionFactory::registerSymmetricCollision(std::unique_ptr<ICollisionHandler> handler)
{
    // For unique_ptr, we can only register one direction unless we clone
    // This is a limitation of unique_ptr - it can't be copied
    registerCollisionInternal(typeid(T1), typeid(T2), std::move(handler));
    
    // Note: Cannot register reverse direction with same handler due to unique_ptr move semantics
    // Would need a separate handler instance or a different approach
} 
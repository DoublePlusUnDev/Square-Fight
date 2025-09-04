#include "physicsObject.h"

#include <algorithm>

#ifndef CPORTA
#include <SDL3/SDL.h>
#endif

#include "memtrace.h"

const double PhysicsObject::maxIntersectionResolveDistance = 5;
const size_t PhysicsObject::intersectionResolvePasses = 10;
const size_t PhysicsObject::physicsPasses = 10;
const bool PhysicsObject::searchChildrenForColliders = true;

PhysicsObject::PhysicsObject(const Transform& transform, const std::vector<Collider*>& colliders)
: Transform(transform),
velocity({0, 0}), 
acceleration({0, 0}), 
gravity({0, -9.81}), 
maxXVelocity({-100, 100}), 
maxYVelocity({-100, 100}),
colliders(colliders)
{
    if (searchChildrenForColliders)
        this->colliders = findTypeInChildren<Collider>();
}

void PhysicsObject::addTagsFromCollider(const Collider* collider)
{
    for (ColliderTag tag : collider->getTags())
    {
        touchedTags.insert(tag);
    }
}

void PhysicsObject::tryResolveIntersections()
{
    if (Collider::checkIntersectionForList(colliders).empty())
        return;

    Vector2 upOffset = tryResolveIntersectionsInDirection({0, maxIntersectionResolveDistance});
    Vector2 downOffset = tryResolveIntersectionsInDirection({0, -maxIntersectionResolveDistance});
    Vector2 rightOffset = tryResolveIntersectionsInDirection({maxIntersectionResolveDistance, 0});
    Vector2 leftOffset = tryResolveIntersectionsInDirection({-maxIntersectionResolveDistance, 0});

    Vector2 currentOffset = {0, 0};

    if (upOffset != Vector2{0, 0} && (upOffset.length() < currentOffset.length() || currentOffset == Vector2{0, 0}))
        currentOffset = upOffset;

    if (downOffset != Vector2{0, 0} && (downOffset.length() < currentOffset.length() || currentOffset == Vector2{0, 0}))
        currentOffset = downOffset;

    if (rightOffset != Vector2{0, 0} && (rightOffset.length() < currentOffset.length() || currentOffset == Vector2{0, 0}))
        currentOffset = rightOffset;

    if (leftOffset != Vector2{0, 0} && (leftOffset.length() < currentOffset.length() || currentOffset == Vector2{0, 0}))
        currentOffset = leftOffset;

    if (currentOffset != Vector2{0, 0})
        move(currentOffset);
}

Vector2 PhysicsObject::tryResolveIntersectionsInDirection(const Vector2& offset)
{
    std::vector<Collider*> intersects = Collider::checkIntersectionForList(colliders);
    if (intersects.empty())
        return {0, 0};

    Vector2 originalPosition = getPosition();
    
    double moveFraction = 2;

    Vector2 testOffset = offset;
    Vector2 prevOffset = testOffset;
    
    bool success = false;

    for (size_t pass = 0; pass < intersectionResolvePasses; pass++)
    {
        prevOffset = testOffset;
        testOffset = (testOffset - offset / moveFraction);
        move(testOffset);
        std::vector<Collider*> intersects = Collider::checkIntersectionForList(colliders);
        
        if (intersects.empty())
            success = true;     
        else
            testOffset = prevOffset;

        setPosition(originalPosition);
        moveFraction *= 2;
    }

    if (success)
    {
        return testOffset;
    }

    return {0, 0};
}

void PhysicsObject::tryCheck(const Vector2& offset, bool& didIntersect, double& maxBounciness, std::vector<Collider*>& intersects)
{
    move(offset);
    intersects = Collider::checkIntersectionForList(colliders);
    if (!intersects.empty())
    {
        move(-offset);
        didIntersect = true;

        for (Collider* collider : intersects)
        {
            maxBounciness = std::max(collider->getBounciness(), maxBounciness); 
            addTagsFromCollider(collider);
        }
    }
}

void PhysicsObject::physicsUpdate()
{
    //search for changes in children
    if (searchChildrenForColliders)
        colliders = findTypeInChildren<Collider>();

    //check for intersections and try to resolve them
    if (!Collider::checkIntersectionForList(colliders).empty())
        tryResolveIntersections();

    velocity += acceleration * GameRuntime::getPhysicsDeltaTime();
    velocity += gravity * GameRuntime::getPhysicsDeltaTime();

    velocity.x = std::clamp(velocity.x, maxXVelocity.first, maxXVelocity.second);
    velocity.y = std::clamp(velocity.y, maxYVelocity.first, maxYVelocity.second);

    double moveFraction;
    bool didIntersectX;
    bool didIntersectY;
    double bouncinessX;
    double bouncinessY;

    moveFraction = 2;
    didIntersectX = false;
    didIntersectY = false;
    bouncinessX = 0;
    bouncinessY = 0;

    std::vector<Collider*> intersects;
    for (size_t pass = 0; pass < physicsPasses; pass++)
    {
        tryCheck({velocity.x / moveFraction * GameRuntime::getPhysicsDeltaTime(), 0}, didIntersectX, bouncinessX, intersects);

        tryCheck({0, velocity.y / moveFraction * GameRuntime::getPhysicsDeltaTime()}, didIntersectY, bouncinessY, intersects);

        moveFraction *= 2;
    }
    //make up for the leftover
    tryCheck({2 * velocity.x / moveFraction * GameRuntime::getPhysicsDeltaTime(), 0}, didIntersectX, bouncinessX, intersects);

    tryCheck({0, 2 * velocity.y / moveFraction * GameRuntime::getPhysicsDeltaTime()}, didIntersectY, bouncinessY, intersects);


    if (didIntersectX)
        velocity.x = -velocity.x * bouncinessX;

    if (didIntersectY)
        velocity.y = -velocity.y * bouncinessY; 
}

void PhysicsObject::postUpdate()
{
    touchedTags.clear();
}

bool PhysicsObject::tryTeleport(const Vector2& position)
{
    Vector2 oldPosition = getPosition();
    setPosition(position);

    std::vector<Collider*> intersects = Collider::checkIntersectionForList(colliders);

    if (!intersects.empty())
        setPosition(oldPosition);

    return intersects.empty();
}

Vector2 PhysicsObject::getVelocity() const { return velocity; }
void PhysicsObject::setVelocity(const Vector2& velocity) { this->velocity = velocity; }

Vector2 PhysicsObject::getAcceleration() const { return acceleration; }
void PhysicsObject::setAcceleration(const Vector2& acceleration) { this->acceleration = acceleration; }

void PhysicsObject::setGravity(const Vector2& gravity)
{
    this->gravity = gravity;
}

void PhysicsObject::setMaxXVelocity(const std::pair<double, double>& maxXVelocity) { this->maxXVelocity = maxXVelocity; }
void PhysicsObject::setMaxYVelocity(const std::pair<double, double>& maxYVelocity) { this->maxYVelocity = maxYVelocity; }

bool PhysicsObject::checkTag(const ColliderTag tag) const
{
    return touchedTags.count(tag);
}

void PhysicsObject::clearTags()
{
    touchedTags.clear();
}
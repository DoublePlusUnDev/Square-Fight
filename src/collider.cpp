#include "collider.h"

#include <unordered_set>
#include <algorithm>

#include "memtrace.h"

std::vector<Collider*> Collider::colliders = std::vector<Collider*>();

Collider::Collider(const Transform& transform, const ColliderType type, const double bounciness, const std::vector<ColliderTag>& tags)
: Transform(transform), type(type), bounciness(bounciness), tags(tags)
{
    registerCollider();
}

Collider::Collider(const Collider& collider)
: Transform(collider), type(collider.type), bounciness(collider.bounciness), tags(collider.tags)
{
    registerCollider();
}

Collider& Collider::operator=(const Collider& collider)
{
    setLocalPosition(collider.getLocalPosition());
    setLocalScale(collider.getLocalScale());
    type = collider.type;
    bounciness = collider.bounciness;
    tags = collider.tags;
    return *this;
}

Collider::~Collider()
{
    unregisterCollider();
}

void Collider::registerCollider()
{
    colliders.push_back(this);
}

void Collider::unregisterCollider()
{
    auto pos = std::find(colliders.begin(), colliders.end(), this);

    //element is not in list
    if (pos == colliders.end())
        return;

    colliders.erase(pos);
}

bool Collider::checkColliders(const Collider& collider1, const Collider& collider2)
{
    double collider1Top = collider1.getPosition().y + collider1.getScale().y / 2;
    double collider1Bottom = collider1.getPosition().y - collider1.getScale().y / 2;
    double collider2Top = collider2.getPosition().y + collider2.getScale().y / 2;
    double collider2Bottom = collider2.getPosition().y - collider2.getScale().y / 2;

    //vertical check
    if (collider1Bottom > collider2Top || collider2Bottom > collider1Top)
        return false;

    double collider1Right = collider1.getPosition().x + collider1.getScale().x / 2;
    double collider1Left = collider1.getPosition().x - collider1.getScale().x / 2;
    double collider2Right = collider2.getPosition().x + collider2.getScale().x / 2;
    double collider2Left = collider2.getPosition().x - collider2.getScale().x / 2;

    //horizontal check
    if (collider1Left > collider2Right || collider2Left > collider1Right)
        return false;

    return true;
}

std::vector<Collider*> Collider::checkIntersection() const
{
    std::vector<Collider*> result = std::vector<Collider*>();
    
    for (Collider* collider : colliders)
    {
        //skip passive colliders and self
        if (this == collider || collider->type == ColliderType::PASSIVE || !checkColliders(*this, *collider))
            continue;
        
        result.push_back(collider);
    }

    return result;
}

std::vector<Collider*> Collider::checkIntersectionForList(const std::vector<Collider*>& collidersToCheck)
{
    //loop through all colliders to get every unique intersection
    std::unordered_set<Collider*> resultSet;
    for (Collider* collider : collidersToCheck)
    {
        if (collider->type == ColliderType::PASSIVE) continue;

        std::vector<Collider*> intersections = collider->checkIntersection();
        for (Collider* intersection : intersections)
        {
            resultSet.insert(intersection);
        }
    }

    //filter all intersecting colliders to exclude the ones on this object
    std::vector<Collider*> result = std::vector<Collider*>();

    for (Collider* collider : resultSet)
    {
        if (find(collidersToCheck.begin(), collidersToCheck.end(), collider) == collidersToCheck.end())
        {
            result.push_back(collider);
        }
    }

    return result;
}

double Collider::getBounciness() const { return bounciness; }

bool Collider::hasTag(ColliderTag tag) const
{
    return std::find(tags.begin(), tags.end(), tag) != tags.end();
}

std::vector<ColliderTag> Collider::getTags() const { return tags; }
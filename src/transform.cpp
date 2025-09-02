#include "transform.h"

#include <algorithm>
#include <cmath>

#include "memtrace.h"

Vector2::Vector2() : x(0), y(0)
{

}

Vector2::Vector2(const double x, const double y) : x(x), y(y)
{

}

Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;

    return *this;
}
Vector2 Vector2::operator+(const Vector2& other) const
{
    return Vector2(x + other.x, y + other.y);
}

Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}
Vector2 Vector2::operator-(const Vector2& other) const
{
    return Vector2(x - other.x, y - other.y);
}

Vector2& Vector2::operator*=(const double scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}
Vector2 Vector2::operator*(const double scalar) const
{
    return Vector2(x * scalar, y * scalar);
}

Vector2& Vector2::operator/=(const double scalar)
{
    x /= scalar;
    y /= scalar;

    return *this;
}
Vector2 Vector2::operator/(const double scalar) const
{
    return Vector2(x / scalar, y / scalar);
}

bool Vector2::operator==(const Vector2& other) const
{
    return (x == other.x && y == other.y);
}

bool Vector2::operator!=(const Vector2& other) const
{
    return !(*this == other);
}

Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
}

double Vector2::length() const
{
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalize() const
{
    double len = length();
    if (len == 0) return Vector2(0, 0);
    return Vector2(x / len, y / len);
}

Transform::Transform(Transform* const parent, const Vector2& position, const Vector2& scale) 
: position(position), scale(scale), parent(parent), children(std::vector<Transform*>())
{
    if (parent != nullptr)
        parent->addChild(this);
}

Transform::Transform(const Transform& transform)
: position(transform.position), scale(transform.scale), parent(transform.parent)
{
    if (parent != nullptr)
        parent->addChild(this);
}

Transform& Transform::operator=(const Transform& transform)
{
    changeParent(transform.parent);
    position = transform.position;
    scale = transform.scale;
    return *this;
}

Transform::~Transform()
{
    for (Transform* child : children)
    {
        child->changeParent(nullptr);
    }

    if (parent != nullptr)
        parent->removeChild(this);
}

void Transform::addChild(Transform* const child)
{
    //returns if already contained
    auto childPos = find(children.begin(), children.end(), child);
    if (childPos != children.end())
        return;

    children.push_back(child);
}

void Transform::removeChild(Transform* const child)
{
    //returns if not contained
    auto childPos = find(children.begin(), children.end(), child);
    if (childPos == children.end())
        return;

    children.erase(childPos);
}

void Transform::move(const Vector2& offset)
{
    position += offset;
}

Transform* Transform::getParent() const
{
    return parent;
}
    
void Transform::changeParent(Transform* const parent)
{
    if (this->parent == parent) return;

    Vector2 oldPosition = getPosition();
    Vector2 oldScale = getScale();

    Transform* oldParent = this->parent;

    this->parent = parent;
    setPosition(oldPosition);
    setScale(oldScale);

    if (parent != nullptr)
        parent->addChild(this);

    if (oldParent != nullptr)
        oldParent->removeChild(this);
} 

size_t Transform::countChildren() const
{
    return children.size(); 
}

Transform* Transform::getChild(const size_t idx) const
{
    return children[idx];
}

Vector2 Transform::getPosition() const 
{
    if (parent == nullptr)
        return position;
    else
        return Vector2(parent->getPosition().x + parent->getScale().x * position.x, parent->getPosition().y + parent->getScale().y * position.y); 
}
Vector2 Transform::getScale() const 
{
    if (parent == nullptr)
        return scale; 
    else 
        return Vector2(parent->getScale().x * scale.x, parent->getScale().y * scale.y);
}

void Transform::setPosition(const Vector2& position)
{
    if (parent == nullptr)
        this->position = position;

    else
    {
        this->position.x = (position.x - parent->getPosition().x) / parent->getScale().x; 
        this->position.y = (position.y - parent->getPosition().y) / parent->getScale().y; 
    }
}

void Transform::setScale(const Vector2& scale) 
{
    if (parent == nullptr)
        this->scale = scale;
    else
    {
        this->scale.x = scale.x / parent->getScale().x;
        this->scale.y = scale.y / parent->getScale().y;
    }
}

Vector2 Transform::getLocalPosition() const { return position; }
Vector2 Transform::getLocalScale() const { return scale; }

void Transform::setLocalPosition(const Vector2& position) { this->position = position; }
void Transform::setLocalScale(const Vector2& scale) { this->scale = scale; }
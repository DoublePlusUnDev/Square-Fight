#ifndef CPORTA
#include "wall.h"

Wall::Wall(const Transform& transform, const Color& color, const double bounciness, const Vector2& colliderRatio, const std::vector<ColliderTag> colliderTags)
    : Transform(transform), 
      renderer(Transform(this), color, UpdatePriority::WALL_RENDERER), 
      collider(Transform(this, {0, 0}, {colliderRatio.x, colliderRatio.y}), ColliderType::INTERACTIVE, bounciness, colliderTags)
{

}
#endif
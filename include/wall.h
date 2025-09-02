#pragma once
#include "memtrace.h"

#include "boxrenderer.h"
#include "collider.h"

/**
 * @brief Statikus falat reprezentáló osztály a játék világában.
 * 
 * A `Wall` osztály egy statikus falat valósít meg, amely vizuális
 * megjelenítéssel (`BoxRenderer`) rendelkezik, és egy collider segítségével
 * lehetővé teszi, hogy más objektumok nekiütközzenek. A `Transform` osztályból
 * származik, így kezeli a pozíciót és a méretet.
 */
class Wall : public Transform
{
    private:
    BoxRenderer renderer; ///< A fal megjelenítéséért felelős renderelő.
    Collider collider;  ///< A falhoz tartozó collider, amely lehetővé teszi, hogy más objektumok nekiütközzenek.

    public:
    /**
     * @brief Létrehoz egy statikus fal objektumot.
     * 
     * Inicializálja a fal pozícióját, méretét, színét és ütközési tulajdonságait.
     * A fal vizuálisan megjelenik a játék világában, és részt vesz az ütközésdetektálásban.
     * 
     * @param transform A fal pozíciója és mérete a játék világában.
     * @param color A fal színe.
     * @param bounciness Az ütközés visszapattanási együtthatója (0 = nincs visszapattanás, 1 = teljes visszapattanás).
     * @param colliderRatio Az ütközési arány, amely meghatározza a collider méretét a fal méretéhez képest.
     * @param colliderTags A collider címkék, amelyek extra tulajdonságokat adnak a colliderhez.
     */
    Wall(const Transform& transform, const Color& color, const double bounciness = 0, const Vector2& colliderRatio = {1, 1}, const std::vector<ColliderTag> colliderTags = {});
};
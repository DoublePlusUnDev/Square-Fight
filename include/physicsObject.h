#pragma once

#include "core.h"
#include "collider.h"

#include <unordered_set>

/**
 * @brief Egy fizikai objektumot reprezentáló osztály.
 * 
 * A `PhysicsObject` osztály felelős az objektum fizikai tulajdonságainak
 * kezeléséért, beleértve a sebességet, gyorsulást, gravitációt és ütközéseket.
 * Az osztály a `Transform` és `PhysicsUpdatable` osztályokból származik,
 * így támogatja a pozíció, méret és ütközésdetektálás kezelését, valamint
 * a fizikai szimuláció frissítését.
 */
class PhysicsObject : public Transform, PhysicsUpdatable
{
    private:
    static const double maxIntersectionResolveDistance; ///< A maximális távolság, amelyen belül a metszéseket feloldhatja.
    static const size_t intersectionResolvePasses; ///< A metszések feloldásához végrehajtott iterációk száma.
    static const size_t physicsPasses; ///< A fizikai szimuláció során végrehajtott iterációk száma.
    static const bool searchChildrenForColliders; ///< Meghatározza, hogy a gyermekobjektumok collidereit automatikusan keresse-e.

    Vector2 velocity; ///< Az objektum aktuális sebessége.
    Vector2 acceleration; ///< Az objektum aktuális gyorsulása.
    Vector2 gravity; ///< Az objektumra ható gravitációs erő.

    std::pair<double, double> maxXVelocity; ///< Az objektum maximális sebessége az X tengelyen (negatív és pozitív irányban).
    std::pair<double, double> maxYVelocity; ///< Az objektum maximális sebessége az Y tengelyen (negatív és pozitív irányban).

    std::vector<Collider*> colliders; ///< Az objektumhoz tartozó colliderek listája.

    std::unordered_set<ColliderTag> touchedTags; ///< Az objektum által érintett collider címkék halmaza.

    /**
     * @brief Hozzáadja a collider címkéit az érintett címkék közé.
     * 
     * A metódus a megadott collider címkéit (`ColliderTag`) hozzáadja az objektum
     * által érintett címkék halmazához (`touchedTags`).
     * 
     * @param collider A collider, amelynek címkéit hozzá kell adni.
     */
    void addTagsFromCollider(const Collider* collider);

    /**
     * @brief Megpróbálja feloldani a metszéseket más objektumokkal.
     * 
     * A metódus megpróbálja feloldani az ütközéseket a colliderekkel, azáltal 
     * hogy az objektumot a kardinális irányokban mozgatja, amíg a metszések fel nem oldódnak.
     */
    void tryResolveIntersections();

    /**
     * @brief Megpróbálja feloldani a metszéseket egy adott irányban.
     * 
     * A metódus megpróbálja feloldani az ütközéseket a colliderekkel a megadott
     * elmozdulás (offset) irányában. Ha a metszés feloldása sikeres, visszaadja
     * az új elmozdulás vektort. Ha nem sikerül feloldani a metszést, akkor
     * visszaadja a null vektort.
     * 
     * @param offset Az elmozdulás vektora, amelyet az objektumra alkalmazni kell.
     * @return Az új elmozdulás vektora, amely a metszés feloldásához szükséges.
     */
    Vector2 tryResolveIntersectionsInDirection(const Vector2& offset);

    /**
     * @brief Megpróbálja az objektumot a megadott elmozdulással elmozgatni és ellenőrzi, 
     * hogy az objektum az elmozdulás után ütközik-e más colliderekkel.
     * 
     * A metódus megpróbálja az objektumot a megadott elmozdulással (offset) mozgatni, majd ellenőrzi,
     * hogy az objektum colliderei metszenek-e más colliderekkel. Ha ütközés történik, az objektumot
     * visszamozgatja az eredeti pozícióba, és frissíti az ütközés állapotát, valamint az ütközési
     * visszapattanás (bounciness) értékét.
     * 
     * @param offset Az elmozdulás vektora, amelyet az objektumra alkalmazni kell.
     * @param didIntersect Egy referencia a logikai változóra, amely true értéket kap, ha ütközés történt.
     * @param maxBounciness Egy referencia a double változóra, amely az ütközésben részt vevő colliderek
     *                      maximális visszapattanási értékét tárolja.
     * @param intersects Egy referencia a colliderek vektorára, amely tartalmazza azokat a collidereket,
     *                   amelyekkel az objektum ütközött.
     */
    void tryCheck(const Vector2& offset, bool& didIntersect, double& maxBounciness, std::vector<Collider*>& intersects);

    public:
    /**
     * @brief Létrehoz egy PhysicsObject objektumot.
     * 
     * A konstruktor inicializálja az objektum pozícióját, méretét és a hozzá
     * tartozó collidereket. Az objektum a megadott collidereket használja az
     * ütközésdetektáláshoz.
     * 
     * @param transform Az objektum pozíciója és mérete a játék világában.
     * @param colliders Az objektumhoz tartozó colliderek listája.
     */
    PhysicsObject(const Transform& transform, const std::vector<Collider*>& colliders);

    /**
     * @brief A fizikai szimuláció frissítése.
     * 
     * A metódus frissíti az objektum pozícióját, sebességét és gyorsulását
     * a fizikai szimuláció szabályai alapján. Kezeli az ütközéseket a colliderekkel,
     * és figyelembe veszi az ütközési visszapattanásokat (bounciness).
     */
    void physicsUpdate() override;

    /**
     * @brief A címkék törlése, az `update` metódus után.
     */
    void postUpdate() override;

    /**
     * @brief Az objektum pozíciójának közvetlen módosítása (teleportálás).
     * 
     * A metódus megpróbálja az objektumot a megadott pozícióra teleportálni.
     * Az ütközések elkerülése érdekében ellenőrzi, hogy a célpozíció érvényes-e
     * a colliderekkel való metszés szempontjából.
     * 
     * **Fontos:** A metódus használata előtt győződj meg arról, hogy az objektumhoz
     * tartozó colliderek megfelelően inicializálva vannak. Ha a `searchChildrenForColliders`
     * beállítás `true`, akkor érdemes legalább egy `physicsUpdate` hívást végrehajtani
     * a teleportálás előtt. Ellenkező esetben a colliderek listáját a konstruktorban
     * kell megfelelően inicializálni.
     * 
     * @param position A célpozíció, ahová az objektumot teleportálni kell.
     * @return true, ha a teleportálás sikeres, különben false.
     */
    bool tryTeleport(const Vector2& position);

    /**
     * @brief Visszaadja az objektum aktuális sebességét.
     * 
     * @return Az objektum aktuális sebessége.
     */
    Vector2 getVelocity() const;

    /**
     * @brief Beállítja az objektum sebességét.
     * 
     * @param velocity Az új sebesség vektora.
     */
    void setVelocity(const Vector2& velocity);
    
    /**
     * @brief Visszaadja az objektum aktuális gyorsulását.
     * 
     * @return Az objektum aktuális gyorsulása.
     */
    Vector2 getAcceleration() const;

    /**
     * @brief Beállítja az objektum gyorsulását.
     * 
     * @param acceleration Az új gyorsulás vektora.
     */
    void setAcceleration(const Vector2& acceleration);
    
    /**
     * @brief Beállítja az objektumra ható gravitációt.
     * 
     * @param gravity Az új gravitációs erő vektora.
     */
    void setGravity(const Vector2& gravity);

    /**
     * @brief Beállítja az objektum maximális sebességét az X tengelyen.
     * 
     * @param maxXVelocity Az új maximális sebesség (negatív és pozitív irányban).
     */
    void setMaxXVelocity(const std::pair<double, double>& maxXVelocity);

    /**
     * @brief Beállítja az objektum maximális sebességét az Y tengelyen.
     * 
     * @param maxYVelocity Az új maximális sebesség (negatív és pozitív irányban).
     */
    void setMaxYVelocity(const std::pair<double, double>& maxYVelocity);

    /**
     * @brief Visszaadja hogy az objektum érintette-e a megadott collider címkét 
     * a legutóbbi `update` óta.
     * 
     * @return true, ha az objektum érintette a megadott collider címkét, különben false.
     */
    bool checkTag(const ColliderTag tag) const;

    /**
     * @brief Törli az összes érintett collider címkét.
     * 
     * A metódus eltávolítja az összes érintett collider címkét az objektum
     * `touchedTags` halmazából. Ezt minden `update` után meghívja a `postUpdate`.
     */
    void clearTags();
};
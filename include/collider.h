<<<<<<< HEAD
#pragma once

#include "transform.h"

#include <vector>

/**
 * @brief Collider típusok.
 * 
 * Meghatározza, hogy a collider részt vesz e az ütközésekben vagy sem.
 * - INTERACTIVE: részt vesz az ütközésekben
 * - PASSIVE: nem vesz részt az ütközésekben
 */
enum class ColliderType
{
    INTERACTIVE,
    PASSIVE
};

/**
 * @brief Collider címkék.
 * 
 * Meghatározza a collider típusát, amely extra tulajdonságokat rendel
 * a colliderhez. 
 * - DEADLY: játékost megölő collider
 */
enum class ColliderTag
{
    DEADLY,
    PLAYER
};

/**
 * @brief Meghatározza egy objektum fizikai határait.
 * 
 * A `Collider` osztály felelős az objektum fizikai határainak meghatározásáért
 * és az ütközések detektálásáért. Az osztály a `Transform` osztályból származik,
 * így rendelkezik pozícióval és mérettel, amelyeket az ütközésdetektálás során használ.
 * 
 * A `Collider` osztály statikus listát tart fenn az összes colliderről, amely
 * lehetővé teszi az ütközések globális ellenőrzését.
 */
class Collider : public Transform
{
    private:
    static std::vector<Collider*> colliders; ///< Az összes collider statikus listája az ütközések ellenőrzéséhez.

    ColliderType type; ///< A collider típusa (interaktív vagy passzív).
    double bounciness; ///< Az ütközéskor visszapattanási együttható (0 = nincs visszapattanás, 1 = teljes visszapattanás).
    std::vector<ColliderTag> tags; ///< A collider címkék, amelyek extra tulajdonságokat rendelnek a colliderhez.

    /**
     * @brief Regisztrálja a collidert a statikus listába.
     */
    void registerCollider();

    /**
     * @brief Törli a collidert a statikus listából.
     */
    void unregisterCollider();

    public:
    /**
     * @brief Létrehoz egy Collider objektumot.
     * 
     * Létrehoz egy Collider objektumot a megadott pozícióval, mérettel és tulajdonságokkal.
     * Az objektum automatikusan hozzáadódik a statikus collider listához, így részt vesz
     * az ütközésdetektálásban.
     * 
     * @param transform Az objektum pozíciója és mérete a játék világában.
     * @param type A collider típusa (interaktív vagy passzív).
     * @param bounciness Az ütközéskor visszapattanás mértéke (0 = nincs visszapattanás, 1 = teljes visszapattanás).
     * @param tags A collider címkék, amelyek extra tulajdonságokat rendelnek a colliderhez.
     */
    Collider(const Transform& transform, const ColliderType type = ColliderType::INTERACTIVE, const double bounciness = 0, const std::vector<ColliderTag>& tags = {});

    /**
     * @brief Másoló konstruktor.
     * 
     * Létrehoz egy új Collider objektumot egy meglévő Collider alapján.
     * Az új objektum automatikusan hozzáadódik a statikus collider listához,
     * így részt vesz az ütközésdetektálásban.
     * 
     * @param collider A másolandó Collider objektum.
     */
    Collider(const Collider& collider);

    /**
     * @brief Értékadás operátor.
     * 
     * Egy meglévő Collider objektum adatait másolja egy másik Collider objektumba.
     * Az értékadás nem módosítja a statikus collider listát.
     * 
     * @param collider A másolandó Collider objektum.
     * @return Az aktuális Collider objektum referenciája.
     */
    Collider& operator=(const Collider& collider);

    /**
     * @brief Megsemmisíti a Collider objektumot.
     * 
     * Megsemmisíti a Collider objektumot és eltávolítja a satikus collider listából.
     */
    ~Collider();

    /**
     * @brief Ellenőrzi, hogy két collider metszi-e egymást.
     * 
     * Ellenőrzi, hogy két collider metszi-e egymást.
     * 
     * @param collider1 Az egyik collider.
     * @param collider2 A másik collider.
     * 
     * @return true, ha a két collider metszi egymást, egyébként false.
     */
    static bool checkColliders(const Collider& collider1, const Collider& collider2);
    
    /**
     * @brief Ellenőrzi, hogy a collider metszi-e a statikus collider listában szereplő collidereket.
     * 
     * Az ütközésdetektálás során ellenőrzi, hogy az aktuális collider
     * átfedi-e bármelyik collidert a statikus collider listában.
     * 
     * @return Azok a colliderek, amelyek metszik az aktuális collidert.
     */
    std::vector<Collider*> checkIntersection() const;

    /**
     * @brief Ellenőrzi, hogy a megadott colliderek listájában lévő colliderek közül
     * bármelyik metszi-e a statikus collider listában szereplő collidereket.
     * 
     * Az ütközésdetektálás során minden megadott colliderhez megkeresi azokat a collidereket,
     * amelyekkel ütköznek, és ezeket egy halmazba gyűjti, hogy az eredmény egyedi legyen.
     * 
     * @param collidersToCheck A colliderek listája, amelyeket ellenőrizni kell.
     * 
     * @return Azok a colliderek, amelyek metszik a vizsgált collidereket.
     */
    static std::vector<Collider*> checkIntersectionForList(const std::vector<Collider*>& collidersToCheck);    

    /**
     * @brief Visszaadja a collider visszapattanási együtthatóját.
     * 
     * A visszapattanási együttható határozza meg, hogy az ütközés során
     * az objektum mennyire "rugalmas":
     * - 0: Nincs visszapattanás
     * - 1: Teljes visszapattanás
     * 
     * @return A visszapattanási együttható értéke.
     */
    double getBounciness() const;

    /**
     * @brief Ellenőrzi, hogy egy adott címke megtalálható-e a collider címkéi között.
     * 
     * A címkék extra tulajdonságokat rendelnek a colliderhez.
     * 
     * @param tag A keresett címke.
     */
    bool hasTag(const ColliderTag tag) const; 

    /**
     * @brief Visszaadja a collider címkéit.
     * 
     * A címkék extra tulajdonságokat rendelnek a colliderhez.
     * 
     * @return A collider címkéinek listája.
     */
    std::vector<ColliderTag> getTags() const;
=======
#pragma once

#include "transform.h"

#include <vector>

/**
 * @brief Collider típusok.
 * 
 * Meghatározza, hogy a collider részt vesz e az ütközésekben vagy sem.
 * - INTERACTIVE: részt vesz az ütközésekben
 * - PASSIVE: nem vesz részt az ütközésekben
 */
enum class ColliderType
{
    INTERACTIVE,
    PASSIVE
};

/**
 * @brief Collider címkék.
 * 
 * Meghatározza a collider típusát, amely extra tulajdonságokat rendel
 * a colliderhez. 
 * - DEADLY: játékost megölő collider
 */
enum class ColliderTag
{
    DEADLY,
    PLAYER
};

/**
 * @brief Meghatározza egy objektum fizikai határait.
 * 
 * A `Collider` osztály felelős az objektum fizikai határainak meghatározásáért
 * és az ütközések detektálásáért. Az osztály a `Transform` osztályból származik,
 * így rendelkezik pozícióval és mérettel, amelyeket az ütközésdetektálás során használ.
 * 
 * A `Collider` osztály statikus listát tart fenn az összes colliderről, amely
 * lehetővé teszi az ütközések globális ellenőrzését.
 */
class Collider : public Transform
{
    private:
    static std::vector<Collider*> colliders; ///< Az összes collider statikus listája az ütközések ellenőrzéséhez.

    ColliderType type; ///< A collider típusa (interaktív vagy passzív).
    double bounciness; ///< Az ütközéskor visszapattanási együttható (0 = nincs visszapattanás, 1 = teljes visszapattanás).
    std::vector<ColliderTag> tags; ///< A collider címkék, amelyek extra tulajdonságokat rendelnek a colliderhez.

    /**
     * @brief Regisztrálja a collidert a statikus listába.
     */
    void registerCollider();

    /**
     * @brief Törli a collidert a statikus listából.
     */
    void unregisterCollider();

    public:
    /**
     * @brief Létrehoz egy Collider objektumot.
     * 
     * Létrehoz egy Collider objektumot a megadott pozícióval, mérettel és tulajdonságokkal.
     * Az objektum automatikusan hozzáadódik a statikus collider listához, így részt vesz
     * az ütközésdetektálásban.
     * 
     * @param transform Az objektum pozíciója és mérete a játék világában.
     * @param type A collider típusa (interaktív vagy passzív).
     * @param bounciness Az ütközéskor visszapattanás mértéke (0 = nincs visszapattanás, 1 = teljes visszapattanás).
     * @param tags A collider címkék, amelyek extra tulajdonságokat rendelnek a colliderhez.
     */
    Collider(const Transform& transform, const ColliderType type = ColliderType::INTERACTIVE, const double bounciness = 0, const std::vector<ColliderTag>& tags = {});

    /**
     * @brief Másoló konstruktor.
     * 
     * Létrehoz egy új Collider objektumot egy meglévő Collider alapján.
     * Az új objektum automatikusan hozzáadódik a statikus collider listához,
     * így részt vesz az ütközésdetektálásban.
     * 
     * @param collider A másolandó Collider objektum.
     */
    Collider(const Collider& collider);

    /**
     * @brief Értékadás operátor.
     * 
     * Egy meglévő Collider objektum adatait másolja egy másik Collider objektumba.
     * Az értékadás nem módosítja a statikus collider listát.
     * 
     * @param collider A másolandó Collider objektum.
     * @return Az aktuális Collider objektum referenciája.
     */
    Collider& operator=(const Collider& collider);

    /**
     * @brief Megsemmisíti a Collider objektumot.
     * 
     * Megsemmisíti a Collider objektumot és eltávolítja a satikus collider listából.
     */
    ~Collider();

    /**
     * @brief Ellenőrzi, hogy két collider metszi-e egymást.
     * 
     * Ellenőrzi, hogy két collider metszi-e egymást.
     * 
     * @param collider1 Az egyik collider.
     * @param collider2 A másik collider.
     * 
     * @return true, ha a két collider metszi egymást, egyébként false.
     */
    static bool checkColliders(const Collider& collider1, const Collider& collider2);
    
    /**
     * @brief Ellenőrzi, hogy a collider metszi-e a statikus collider listában szereplő collidereket.
     * 
     * Az ütközésdetektálás során ellenőrzi, hogy az aktuális collider
     * átfedi-e bármelyik collidert a statikus collider listában.
     * 
     * @return Azok a colliderek, amelyek metszik az aktuális collidert.
     */
    std::vector<Collider*> checkIntersection() const;

    /**
     * @brief Ellenőrzi, hogy a megadott colliderek listájában lévő colliderek közül
     * bármelyik metszi-e a statikus collider listában szereplő collidereket.
     * 
     * Az ütközésdetektálás során minden megadott colliderhez megkeresi azokat a collidereket,
     * amelyekkel ütköznek, és ezeket egy halmazba gyűjti, hogy az eredmény egyedi legyen.
     * 
     * @param collidersToCheck A colliderek listája, amelyeket ellenőrizni kell.
     * 
     * @return Azok a colliderek, amelyek metszik a vizsgált collidereket.
     */
    static std::vector<Collider*> checkIntersectionForList(const std::vector<Collider*>& collidersToCheck);    

    /**
     * @brief Visszaadja a collider visszapattanási együtthatóját.
     * 
     * A visszapattanási együttható határozza meg, hogy az ütközés során
     * az objektum mennyire "rugalmas":
     * - 0: Nincs visszapattanás
     * - 1: Teljes visszapattanás
     * 
     * @return A visszapattanási együttható értéke.
     */
    double getBounciness() const;

    /**
     * @brief Ellenőrzi, hogy egy adott címke megtalálható-e a collider címkéi között.
     * 
     * A címkék extra tulajdonságokat rendelnek a colliderhez.
     * 
     * @param tag A keresett címke.
     */
    bool hasTag(const ColliderTag tag) const; 

    /**
     * @brief Visszaadja a collider címkéit.
     * 
     * A címkék extra tulajdonságokat rendelnek a colliderhez.
     * 
     * @return A collider címkéinek listája.
     */
    std::vector<ColliderTag> getTags() const;
>>>>>>> a04c523 (Idk :3)
};
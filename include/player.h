#pragma once

#include "boxrenderer.h"
#include "physicsObject.h"
#include "inputscheme.h"

#include <string>

/**
 * @brief A játékos karaktert reprezentáló osztály.
 * 
 * A `Player` osztály felelős a játékos karakter fizikai és logikai működéséért.
 * Kezeli a játékos mozgását, ugrását, vetődését és ütközéseit. Az osztály az
 * `InputScheme` segítségével dolgozza fel a bemeneteket, és a `PhysicsObject`
 * osztályból származik, így támogatja a fizikai szimulációt és az ütközésdetektálást.
 */
class Player : public PhysicsObject, Updatable
{
    private:
    BoxRenderer renderer; ///< A játékos vizuális megjelenítéséért felelős renderelő.
    Collider collider; ///< A játékos fő collider objektuma, amely az ütközéseket kezeli.
    Collider groundCheck; ///< A talajjal való érintkezés ellenőrzésére szolgáló collider.
    Collider headCheck; ///< A fej fölötti ütközések ellenőrzésére szolgáló collider.

    const InputScheme inputScheme; ///< A játékoshoz tartozó bemeneti kiosztás.
    
    double jumpSpeed = 10.5; ///< Az ugrás sebessége.
    double dashSpeed = 20; ///< A vetődés sebessége.
    double moveAcceleration = 20; ///< A mozgás gyorsulása.
    double turnAcceleration = 55; ///< Az irányváltás gyorsulása.
    double maxSpeed = 8; ///< A maximális vízszintes sebesség.
    double maxFallSpeed = 30; ///< A maximális esési sebesség.
    double floatGravity = 1.2 * 9.81; ///< A gravitáció értéke lassú esés közben.
    double fallGravity = 2.2 * 9.81; ///< A gravitáció értéke gyors esés közben.
    double groundDrag = 30; ///< A talajon ható lassító erő.
    double airDrag = 10; ///< A levegőben ható lassító erő.

    bool hasDied; ///< Jelzi, hogy a játékos jelenleg halott állapotban van-e.

    /**
     * @brief A játékos irányításának kezelése.
     * 
     * A metódus az `InputScheme` alapján dolgozza fel a játékos bemeneteit,
     * és ennek megfelelően állítja be a mozgást, ugrást, vetődést és gravitációt.
     */
    void controlPlayer();

    /**
     * @brief Ellenőrzi, hogy a játékos a pálya határain belül van-e.
     * 
     * Ha a játékos elhagyja a pálya határait, a metódus a pálya másik oldalára
     * teleportálja, biztosítva a folyamatos játékmenetet.
     */
    void boundsCheck();

    /**
     * @brief Ellenőrzi, hogy a játékos meghalt-e.
     * 
     * A metódus ellenőrzi, hogy a játékos halálos ütközésbe került-e, például
     * másik játékos a játékos fejére ugrással vagy egy halálos objektummal való 
     * érintkezés miatt.
     * 
     * @return true, ha a játékos meghalt, különben false.
     */
    bool checkDeath() const;

    /**
     * @brief Ellenőrzi, hogy a játékos a talajon van-e.
     * 
     * A metódus a `groundCheck` collider segítségével vizsgálja, hogy a játékos
     * érintkezik-e a talajjal. Ha a collider nem halálos objektumot metsz, akkor
     * a játékos a talajon van. 
     * 
     * A halálosságot azért szükséges ellenőrizni, mivel az ellenőrzés valamivel 
     * hamarabb történik, mint a tényleges ütközésdetektálás, így a játékos el
     * tud ugrani a halálos objektumról, mielőtt az ténylegesen megölné.
     * 
     * @return true, ha a játékos a talajon van, különben false.
     */
    bool isGrounded() const;

    public:
    /**
     * @brief Létrehoz egy `Player` objektumot.
     * 
     * Inicializálja a játékos színét, bemeneti kiosztását és fizikai tulajdonságait.
     * 
     * @param color A játékos színe.
     * @param inputScheme A játékoshoz tartozó bemeneti kiosztás.
     */
    Player(const Color& color, const InputScheme& inputScheme);

    /**
     * @brief A játékos frissítése.
     * 
     * A metódus a játékos mozgását, ütközéseit és állapotát kezeli a játék
     * főciklusában.
     */
    void update() override;

    /**
     * @brief A játékos állapotának visszaállítása.
     * 
     * A metódus visszaállítja a játékos pozícióját, sebességét és állapotát
     * a megadott kezdőpozícióra. Emellett alaphelyzetbe állítja a halál állapotát
     * és a mozgással kapcsolatos paramétereket.
     * 
     * @param resetPosition A játékos új pozíciója.
     */
    void reset(const Vector2& resetPosition);

    /**
     * @brief Visszaadja, hogy a játékos meghalt-e.
     * 
     * @return true, ha a játékos meghalt, különben false.
     */
    bool isDead() const;
};
#pragma once
#include "memtrace.h"

#include <vector>

/**
 * @brief Két dimenziós vektort reprezentáló struktúra.
 * 
 * A `Vector2` struktúra X és Y komponensekkel rendelkező vektorokat reprezentál,
 * amelyeket pozíciók, méretek vagy sebességek tárolására használhatunk.
 * Támogatja az alapvető matematikai műveleteket, például összeadást, kivonást,
 * szorzást és osztást.
 */
struct Vector2
{
    double x; ///< A vektor X komponense.
    double y; ///< A vektor Y komponense.

    /**
     * @brief Alapértelmezett konstruktor, amely (0, 0) értékekkel inicializálja a vektort.
     */
    Vector2();

    /**
     * @brief Konstruktor, amely a megadott X és Y értékekkel inicializálja a vektort.
     * 
     * @param x A vektor X komponense.
     * @param y A vektor Y komponense.
     */
    Vector2(const double x, const double y);

    /**
     * @brief Hozzáad egy másik vektort ehhez a vektorhoz.
     * 
     * @param other A hozzáadandó vektor.
     * @return Az aktuális vektor referenciája.
     */
    Vector2& operator+=(const Vector2& other);

    /**
     * @brief Két vektor összeadása.
     * 
     * @param other A hozzáadandó vektor.
     * @return Az összeadás eredményeként kapott új vektor.
     */
    Vector2 operator+(const Vector2& other) const;

    /**
     * @brief Kivon egy másik vektort ebből a vektorból.
     * 
     * @param other A kivonandó vektor.
     * @return Az aktuális vektor referenciája.
     */
    Vector2& operator-=(const Vector2& other);

    /**
     * @brief Két vektor kivonása.
     * 
     * @param other A kivonandó vektor.
     * @return A kivonás eredményeként kapott új vektor.
     */
    Vector2 operator-(const Vector2& other) const;

    /**
     * @brief Megszorozza a vektort egy skalárral.
     * 
     * @param scalar A szorzó értéke.
     * @return Az aktuális vektor referenciája.
     */
    Vector2& operator*=(const double scalar);

    /**
     * @brief Egy vektor és egy skalár szorzása.
     * 
     * @param scalar A szorzó értéke.
     * @return Az új vektor, amely a szorzás eredménye.
     */
    Vector2 operator*(const double scalar) const;

    /**
     * @brief Elosztja a vektort egy skalárral.
     * 
     * @param scalar Az osztó értéke.
     * @return Az aktuális vektor referenciája.
     */
    Vector2& operator/=(const double scalar);

    /**
     * @brief Egy vektor és egy skalár osztása.
     * 
     * @param scalar Az osztó értéke.
     * @return Az új vektor, amely az osztás eredménye.
     */
    Vector2 operator/(const double scalar) const;

    /**
     * @brief Összehasonlítja ezt a vektort egy másikkal.
     * 
     * @param other A másik vektor, amellyel összehasonlítjuk.
     * @return true, ha a két vektor egyenlő, különben false.
     */
    bool operator==(const Vector2& other) const; 

    /**
     * @brief Összehasonlítja ezt a vektort egy másikkal.
     * 
     * @param other A másik vektor, amellyel összehasonlítjuk.
     * @return true, ha a két vektor nem egyenlő, különben false.
     */
    bool operator!=(const Vector2& other) const;

    /**
     * @brief Egy vektor megfordítása.
     * 
     * @return A megfordított vektor.
     */
    Vector2 operator-() const; 

    /**
     * @brief Kiszámolja a vektor hosszát.
     * 
     * @return A vektor hossza.
     */
    double length() const;

    /**
     * @brief Normalizálja a vektort.
     * 
     * A normalizálás során a vektor hosszát 1-re állítja, miközben megőrzi
     * az irányát. Ha a vektor hossza 0, akkor a normalizálás nem hajtható végre.
     * 
     * @return A normalizált vektor.
     */
    Vector2 normalize() const; 
};

/**
 * @brief Hierarchikus transzformációkat kezelő osztály.
 * 
 * A `Transform` osztály egy objektum pozícióját és méretét kezeli, valamint
 * támogatja a szülő-gyermek hierarchiát. Lehetővé teszi a globális és lokális
 * transzformációk számítását a játék világában.
 */
class Transform
{
    private:
    Vector2 position; ///< Az objektum lokális pozíciója.
    Vector2 scale; ///< Az objektum lokális mérete.

    Transform* parent; ///< Az objektum szülője a hierarchiában.
    std::vector<Transform*> children; ///< Az objektum gyermekei a hierarchiában.

    /**
     * @brief Gyermek hozzáadása az objektumhoz.
     * 
     * Metódus csak belső használatra, ha a gyermek globális pozícióját 
     * és méretét meg akarjuk tartani, akkor a gyerek `changeparent` 
     * metódusát kell használni.
     * 
     * @param child A hozzáadandó gyermek objektum.
     */
    void addChild(Transform* const child);

    /**
     * @brief Gyermek eltávolítása az objektumból.
     * 
     * Metódus csak belső használatra, ha a gyermek globális pozícióját 
     * és méretét meg akarjuk tartani, akkor a gyerek `changeparent` 
     * metódusát kell használni.
     * 
     * @param child Az eltávolítandó gyermek objektum.
     */
    void removeChild(Transform* const child);

    public:
    /**
     * @brief Konstruktor.
     * 
     * Inicializálja az objektumot a megadott szülővel, pozícióval és mérettel.
     * 
     * @param parent Az objektum szülője (alapértelmezés szerint nincs szülő).
     * @param position Az objektum pozíciója (alapértelmezés szerint {0, 0}).
     * @param scale Az objektum mérete (alapértelmezés szerint {1, 1}).
     */
    Transform(Transform* const parent = nullptr, const Vector2& position = { 0, 0 }, const Vector2& scale = { 1, 1 });

    /**
     * @brief Másoló konstruktor.
     * 
     * Létrehoz egy új `Transform` objektumot egy meglévő másolataként.
     * 
     * A másoló konstruktor átmásolja az eredeti objektum pozícióját, méretét
     * és szülőjét. Ha az eredeti objektumnak van szülője, az új objektumot
     * automatikusan hozzáadja a szülő gyermekei közé. A gyermekek nem kerülnek
     * másolásra, mivel a másoló konstruktor csak az aktuális objektumot másolja.
     * 
     * @param transform A másolandó `Transform` objektum.
     */
    Transform(const Transform& transform);

    /**
     * @brief Értékadás operátor.
     * 
     * Egy meglévő `Transform` objektum adatait másolja az aktuális objektumba.
     * 
     * Az értékadás operátor átmásolja az eredeti objektum pozícióját, méretét
     * és szülőjét. Az aktuális objektumot eltávolítja a korábbi szülőjéből,
     * és hozzáadja az új szülő gyermekei közé. A gyermekek nem kerülnek másolásra,
     * mivel az értékadás csak az aktuális objektumra vonatkozik.
     * 
     * @param transform A másolandó `Transform` objektum.
     * @return Az aktuális objektum referenciája.
     */
    Transform& operator=(const Transform& transform);

    /**
     * @brief Destruktor.
     * 
     * A destruktor felszabadítja az objektum által használt erőforrásokat, és eltávolítja
     * az objektumot a szülő hierarchiájából. Az alábbi lépéseket hajtja végre:
     * 
     * 1. **Gyermekek szülőjének eltávolítása**: Az összes gyermek `Transform` objektum
     *    szülőjét `nullptr`-ra állítja, így megszakítja a kapcsolatot a gyermekekkel.
     * 
     * 2. **Eltávolítás a szülő gyermekei közül**: Ha az objektumnak van szülője,
     *    eltávolítja magát a szülő gyermekei közül.
     * 
     * Ez biztosítja, hogy a hierarchia megfelelően frissüljön, és ne maradjanak
     * érvénytelen hivatkozások.
     */
    virtual ~Transform();

    /**
     * @brief Az objektum elmozdítása.
     * 
     * Az objektum pozícióját a megadott eltolással módosítja.
     * 
     * @param offset Az elmozdulás vektora.
     */
    void move(const Vector2& offset);

    /**
     * @brief Visszaadja az objektum szülőjét.
     * 
     * @return Az objektum szülője, vagy nullptr, ha nincs szülő.
     */
    Transform* getParent() const;

    /**
     * @brief Az objektum szülőjének módosítása.
     * 
     * Az objektumot áthelyezi egy új szülő alá a hierarchiában.
     * A globális pozíciót és méretet nem változtatja meg.
     * A lokális pozíciót és méretet igazítja az új szülőhöz.
     * 
     * @param parent Az új szülő objektum.
     */
    void changeParent(Transform* const parent); 

    /**
     * @brief Visszaadja az objektum gyermekei számát.
     * 
     * @return Az objektum gyermekei száma.
     */
    size_t countChildren() const;

    /**
     * @brief Visszaadja az objektum egy adott gyermekét.
     * 
     * @param idx A gyermek indexe.
     * @return Az adott gyermek objektum.
     */
    Transform* getChild(const size_t idx) const;

    /**
     * @brief Az objektum globális pozíciójának lekérdezése.
     * 
     * A globális pozíció a szülő hierarchiájának figyelembevételével kerül kiszámításra.
     * 
     * @return Az objektum globális pozíciója.
     */
    Vector2 getPosition() const;

    /**
     * @brief Az objektum globális méretének lekérdezése.
     * 
     * A globális méret a szülő hierarchiájának figyelembevételével kerül kiszámításra.
     * 
     * @return Az objektum globális mérete.
     */
    Vector2 getScale() const;

    /**
     * @brief Beállítja az objektum globális pozícióját.
     * 
     * Ha az objektumnak van szülője, a megadott globális pozíciót lokális pozícióvá
     * alakítja a szülő globális pozíciója és mérete alapján. Ha nincs szülője,
     * a pozíció közvetlenül kerül beállításra.
     * 
     * @param position Az új pozíció.
     */
    void setPosition(const Vector2& position);

    /**
     * @brief Beállítja az objektum globális méretét.
     * 
     * Ha az objektumnak van szülője, a megadott globális méretet lokális méretté
     * alakítja a szülő globális mérete alapján. Ha nincs szülője, a méret közvetlenül 
     * kerül beállításra.
     * 
     * @param scale Az új méret.
     */
    void setScale(const Vector2& scale);

    /**
     * @brief Visszaadja az objektum lokális pozícióját.
     * 
     * @return Az objektum lokális pozíciója.
     */
    Vector2 getLocalPosition() const;

    /**
     * @brief Visszaadja az objektum lokális méretét.
     * 
     * @return Az objektum lokális mérete.
     */
    Vector2 getLocalScale() const;

    /**
     * @brief Beállítja az objektum lokális pozícióját.
     * 
     * @param position Az új lokális pozíció.
     */
    void setLocalPosition(const Vector2& position);

    /**
     * @brief Beállítja az objektum lokális méretét.
     * 
     * @param scale Az új lokális méret.
     */
    void setLocalScale(const Vector2& scale);

    /**
     * @brief Keres egy adott típusú objektumot a gyermekek között.
     * 
     * @tparam T A keresett objektum típusa.
     * @return Az adott típusú objektumok listája.
     */
    template <typename T>
    std::vector<T*> findTypeInChildren();
};

#include "transform.inl"
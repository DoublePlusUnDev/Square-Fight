#pragma once

#include "transform.h"
#include "colors.h"
#include <vector>

/**
 * @brief A játék pályáinak kezelésére szolgáló osztály.
 * 
 * A `MapManager` osztály felelős a játék pályáinak betöltéséért, eltávolításáért,
 * és az ezekhez kapcsolódó adatok kezeléséért. Kezeli a pályák elemeit, például
 * falakat, játékosok kezdőpozícióit, háttérszíneket, valamint a győzelemhez
 * szükséges pontszámot.
 */
class MapManager
{
    private:
    /**
     * @brief Egy pályaelem adatait tároló struktúra.
     * 
     * A `MapElement` struktúra egy pályaelem tulajdonságait tárolja, például
     * a pozícióját, méretét, színét, visszapattanási értékét és a collider arányát.
     */
    struct MapElement
    {
        Vector2 position; ///< Az elem pozíciója a pályán.
        Vector2 scale; ///< Az elem mérete.
        Color color; ///< Az elem színe.
        bool deadly; ///< Meghatározza, hogy az elem halálos-e
        double bounciness; ///< Az elem visszapattanási értéke.
        Vector2 colliderRatio; ///< Az elem colliderének aránya a méretéhez képest.

        /**
         * @brief Létrehoz egy `MapElement` objektumot.
         * 
         * Inicializálja a pályaelem tulajdonságait.
         * 
         * @param position Az elem pozíciója.
         * @param scale Az elem mérete.
         * @param color Az elem színe.
         * @param deadly Meghatározza, hogy az elem halálos-e.
         * @param bounciness Az elem visszapattanási értéke.
         * @param colliderRatio Az elem colliderének aránya.
         */
        MapElement(const Vector2& position, const Vector2& scale, const Color& color, const bool deadly, const double bounciness, const Vector2& colliderRatio);
    };

    /**
     * @brief Egy pálya adatait tároló struktúra.
     * 
     * A `Map` struktúra egy pálya tulajdonságait tárolja, például a magasságát,
     * háttérszínét, a győzelemhez szükséges pontszámot, a játékosok kezdőpozícióit
     * és az elemek listáját.
     */
    struct Map
    {
        double mapHeight; ///< A pálya magassága.
        Color backgroundColor; ///< A pálya háttérszíne.
        int scoreToWin; ///< A győzelemhez szükséges pontszám.
        Vector2 player1Position; ///< Az első játékos kezdőpozíciója.
        Vector2 player2Position; ///< A második játékos kezdőpozíciója.
        std::vector<MapElement> elements; ///< A pályaelemek listája.
        
        /**
         * @brief Új elem hozzáadása a pályához.
         * 
         * @param position Az elem pozíciója.
         * @param scale Az elem mérete.
         * @param color Az elem színe.
         * @param deadly Meghatározza, hogy az elem halálos-e.
         * @param bounciness Az elem visszapattanási értéke.
         * @param colliderRatio Az elem colliderének aránya.
         */
        void addElement(const Vector2& position, const Vector2& scale, const Color& color, const bool deadly, const double bounciness, const Vector2& colliderRatio);
    };

    std::vector<Map> mapCache; ///< A játékban elérhető pályák adatai.
    std::vector<Transform*> mapInstance; ///< Az aktuálisan betöltött pálya elemei a játék világában.
    size_t loadedMapId; ///< Az aktuálisan betöltött pálya azonosítója.

    #ifdef CPORTA
    /**
     * JPORTA kompatiblitást szolgáló függvény nem kéne ha a JPORTA működne a filesystem.h-val.
     * 
     * @brief Kilistázza a .gamemap-re végződő file-okat a játékkal egy mappában.
     */
    std::vector<std::string> getGamemapFiles() const;
    #endif

    #ifndef COPRTA
    /**
     * @brief Egy pálya inicializálása a játék világában.
     * 
     * A metódus létrehozza a megadott pálya elemeit, például falakat, és
     * beállítja a pálya háttérszínét és méretét.
     * 
     * @param map A betöltendő pálya adatai.
     */
    void initializeMap(const Map& map);
    #endif

    /**
     * @brief Az aktuálisan betöltött pálya eltávolítása a játék világából.
     * 
     * A metódus törli az aktuálisan betöltött pálya összes elemét, felszabadítja
     * az ezekhez tartozó erőforrásokat, és kiüríti a pályaelemek listáját.
     */
    void discardMap();

    public:
    /**
     * @brief Létrehoz egy `MapManager` objektumot.
     * 
     * Inicializálja a pályakezelőt, és előkészíti a pályák kezeléséhez szükséges
     * adatstruktúrákat.
     */
    MapManager();

    private:
    /**
     * @brief Másoló konstruktor törlése.
     * 
     * A másoló konstruktor törlése megakadályozza a `MapManager` példányok
     * másolását, mivel a pályák és azok elemei nem másolhatók.
     */
    MapManager(const MapManager& mapManager);

    /**
     * @brief Másoló hozzárendelő operátor törlése.
     * 
     * A másoló hozzárendelő operátor törlése megakadályozza a `MapManager`
     * példányok hozzárendelését, mivel a pályák és azok elemei nem másolhatók.
     */
    MapManager& operator=(const MapManager& mapManager);

    public:
    /**
     * @brief Felszabadítja a `MapManager` által használt erőforrásokat.
     * 
     * A destruktor eltávolítja az összes betöltött pályát, és felszabadítja
     * az erőforrásokat.
     */
    ~MapManager();
    
    /**
     * @brief Visszaadja a pályák számát.
     * 
     * @return A pályák száma.
     */
    size_t getMapCount() const;

    /**
     * @brief Lekérdezi egy játékos kezdőpozícióját az aktuális pályán.
     * 
     * A metódus visszaadja az adott pályán lévő játékos kezdőpozícióját.
     * 
     * @param mapId A pálya azonosítója.
     * @param playerId A játékos azonosítója (0 az első játékos, 1 a második játékos).
     * @return A játékos kezdőpozíciója.
     * @throws std::out_of_range Ha a `mapId` vagy a `playerId` érvénytelen.
     */
    Vector2 getPlayerPosition(const size_t playerId) const;
    
    /**
     * @brief Visszaadja a győzelemhez szükséges pontszámot az aktuális pályán.
     * 
     * @return A győzelemhez szükséges pontszám.
     * @throws std::out_of_range Ha a `mapId` érvénytelen.
     */
    int getScoreToWin() const;

    /**
     * @brief Visszaadja a pálya magasságát.
     * 
     * @return A pálya magassága.
     * @throws std::out_of_range Ha a `mapId` érvénytelen.
     */
    double getMapHeight() const;

    #ifndef CPORTA
    /**
     * @brief Betölt egy pályát a játék világába.
     * 
     * A metódus eltávolítja az aktuálisan betöltött pályát, majd betölti
     * a megadott azonosítójú pályát, és inicializálja annak elemeit.
     * 
     * @param mapId A betöltendő pálya azonosítója.
     * @throws std::out_of_range Ha a `mapId` érvénytelen.
     */
    void loadMap(const size_t mapId);
    #endif

    /**
     * @brief Eltávolítja az aktuálisan betöltött pályát a játék világából.
     * 
     * A metódus eltávolítja az összes pályaelemet, és felszabadítja az
     * ezekhez tartozó erőforrásokat.
     */
    void unloadMap();

    #ifdef CPORTA
    /**
     * @brief Visszaadja a megadott pálya adatait szöveges formátumban.
     * 
     * A metódus tesztelési célzattal készült; visszaadja a megadott pálya
     * magasságát, háttérszínét, győzelemhez szükséges pontszámát,
     * valamint a játékosok kezdőpozícióit.
     */
    std::string getSerializedMapInfo(const size_t mapId);

    /**
     * @brief Visszaadja a megadott pályaelem adatait szöveges formátumban.
     * 
     * A metódus tesztelési célzattal készült; visszaadja a megadott pályaelem
     * pozícióját, méretét, színét, halálos jellegét, visszapattanási értékét és 
     * collider arányát.
     */
    std::string getSerializedMapElement(const size_t mapId, const size_t elementId);
    #endif
};
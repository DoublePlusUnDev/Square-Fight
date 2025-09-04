<<<<<<< HEAD
#pragma once

#include "texthandler.h"
#include "mapmanager.h"
#include "player.h"

/**
 * @brief A játékmenetet kezelő osztály.
 * 
 * A `GameManager` osztály felelős a játékmenet irányításáért, beleértve a
 * játékosok pontszámának nyilvántartását, a körök kezelését, a pályák
 * váltását és a győzelmi feltételek ellenőrzését. Az osztály kezeli a
 * játékosok állapotát (például halálukat és újraéledésüket), valamint
 * biztosítja a játék folyamatos működését, beleértve a pályák betöltését
 * és a szöveges visszajelzések megjelenítését.
 */
class GameManager : Updatable
{
    TextHandler textHandler;  ///< A játék közben megjelenített szövegek kezeléséért felelős objektum.
    MapManager mapManager; ///< A pályák betöltéséért, váltásáért és kezeléséért felelős objektum.

    std::string player1Name = "Blue"; ///< Az első játékos neve, amely megjelenik a játékban.
    Color player1Color = makeColor(0, 0, 200); ///< Az első játékos színe.
    std::string player2Name = "Red"; ///< A második játékos neve, amely megjelenik a játékban.
    Color player2Color = makeColor(200, 0, 0); ///< A második játékos színe.

    double resetTime = 0.5; ///< A játékos halála után az újraindításig eltelt idő másodpercben.

    Player player1; ///< Az első játékos objektuma, amely a játékos állapotát és viselkedését reprezentálja.
    Player player2; ///< A második játékos objektuma, amely a játékos állapotát és viselkedését reprezentálja.

    int player1Score; ///< Az első játékos aktuális pontszáma.
    int player2Score; ///< A második játékos aktuális pontszáma.
    int round; ///< Az aktuális kör száma.

    double timeUntilReset; ///< Az újraindításig hátralévő idő másodpercben.
    bool shouldReset; ///< Jelzi, hogy elindult-e az újraindítási folyamat.

    /**
     * @brief A GameManager osztály konstruktora.
     * 
     * Inicializálja a játékosokat, a pályakezelőt és a szövegkezelőt.
     * Beállítja a játékosok színét és nevét, valamint a győzelemhez szükséges
     * pontszámot. A konstruktor automatikusan betölti az első pályát.
     */
    GameManager();

    /**
     * @brief A GameManager osztály másoló konstruktora.
     * 
     * A másoló konstruktor megakadályozza a GameManager példányok másolását,
     * mivel a játékmenet egyedi példányt igényel.
     */
    GameManager(const GameManager& gameManager);

    /**
     * @brief A GameManager osztály másoló hozzárendelő operátora.
     * 
     * A másoló hozzárendelő operátor megakadályozza a GameManager példányok
     * hozzárendelését, mivel a játékmenet egyedi példányt igényel.
     */
    GameManager& operator=(const GameManager& gameManager);

    /**
     * @brief Ellenőrzi a játékosok állapotát és kezeli a győzelmet.
     * 
     * A metódus ellenőrzi, hogy valamelyik játékos meghalt-e. Ha egy játékos
     * meghal, a másik játékos pontszáma növekszik, és elindul az újraindítási
     * folyamat. Ha valamelyik játékos eléri a győzelemhez szükséges pontszámot,
     * a játék új pályára vált, és megjeleníti a győztes nevét.
     */
    void checkForWin();

    /**
     * @brief Kezeli az újraindítási folyamat visszaszámlálását.
     * 
     * A metódus csökkenti a `timeUntilReset` értékét a játék frissítési
     * ciklusai alapján. Ha az érték eléri a nullát, újraindítja a játékot.
     */
    void countReset();

    /**
     * @brief Visszaállítja a játék állapotát egy új körhöz.
     * 
     * A metódus visszaállítja a játékosok pozícióját és állapotát, növeli
     * a győztes játékos pontszámát, és ellenőrzi, hogy elérte-e a győzelemhez
     * szükséges pontszámot. Ha igen, a játék új pályára vált.
     */
    void resetGame();

    /**
     * @brief Visszaadja a jelenlegi pálya indexét.
     * 
     * A metódus visszaadja a jelenleg aktív pálya indexét, amelyet a
     * `MapManager` kezel. Ez az index határozza meg, hogy melyik pálya
     * van betöltve a játékban.
     * 
     * @return A jelenlegi pálya indexe.
     */
    size_t getMapId() const;

    /**
     * @brief A következő pálya számának meghatározása.
     * 
     * A metódus a jelenlegi pálya indexét növeli, és betölti a következő pályát
     * a `MapManager` segítségével. Ha nincs több elérhető pálya, a metódus
     * visszatér az első pályára.
     */
    void nextMap();

    public:
    /**
     * @brief Singleton minta megvalósítása.
     * 
     * A metódus biztosítja, hogy csak egy példány létezzen a `GameManager`
     * osztályból. Ha a példány még nem létezik, létrehozza azt.
     * 
     * @return A `GameManager` osztály egyetlen példánya.
     */
    static GameManager& getInstance();

    /**
     * @brief A `GameManager` osztály példánya erőforrásainak felszabadítása.
     * 
     * A metódus biztosítja, hogy a `GameManager` osztály példánya és
     * az összes kapcsolódó erőforrás felszabaduljon, amikor a játék
     * befejeződik
     */
    void shutDown();

    /**
     * @brief A játékmenet frissítése.
     * 
     * A metódus a játék főciklusában kerül meghívásra. Ellenőrzi a játékosok
     * halálát, szükség esetén növeli a győztes pontszámát, és elindítja az
     * újraindítási folyamatot. Ha a győzelemhez szükséges pontszámot elérte
     * valamelyik játékos, a játék új pályára vált.
     */
    void update() override;

    /**
     * @brief Visszaadja a jelenleg betöltött pálya szélességét.
     *
     * @return A pálya szélessége.
     */
    double getMapWidth() const;

    /**
     * @brief Visszaadja a jelenleg betöltött pálya magasságát.
     *
     * @return A pálya magassága.
     */
    double getMapHeight() const;
=======
#pragma once

#include "texthandler.h"
#include "mapmanager.h"
#include "player.h"

/**
 * @brief A játékmenetet kezelő osztály.
 * 
 * A `GameManager` osztály felelős a játékmenet irányításáért, beleértve a
 * játékosok pontszámának nyilvántartását, a körök kezelését, a pályák
 * váltását és a győzelmi feltételek ellenőrzését. Az osztály kezeli a
 * játékosok állapotát (például halálukat és újraéledésüket), valamint
 * biztosítja a játék folyamatos működését, beleértve a pályák betöltését
 * és a szöveges visszajelzések megjelenítését.
 */
class GameManager : Updatable
{
    TextHandler textHandler;  ///< A játék közben megjelenített szövegek kezeléséért felelős objektum.
    MapManager mapManager; ///< A pályák betöltéséért, váltásáért és kezeléséért felelős objektum.

    std::string player1Name = "Blue"; ///< Az első játékos neve, amely megjelenik a játékban.
    Color player1Color = makeColor(0, 0, 200); ///< Az első játékos színe.
    std::string player2Name = "Red"; ///< A második játékos neve, amely megjelenik a játékban.
    Color player2Color = makeColor(200, 0, 0); ///< A második játékos színe.

    double resetTime = 0.5; ///< A játékos halála után az újraindításig eltelt idő másodpercben.

    Player player1; ///< Az első játékos objektuma, amely a játékos állapotát és viselkedését reprezentálja.
    Player player2; ///< A második játékos objektuma, amely a játékos állapotát és viselkedését reprezentálja.

    int player1Score; ///< Az első játékos aktuális pontszáma.
    int player2Score; ///< A második játékos aktuális pontszáma.
    int round; ///< Az aktuális kör száma.

    double timeUntilReset; ///< Az újraindításig hátralévő idő másodpercben.
    bool shouldReset; ///< Jelzi, hogy elindult-e az újraindítási folyamat.

    /**
     * @brief A GameManager osztály konstruktora.
     * 
     * Inicializálja a játékosokat, a pályakezelőt és a szövegkezelőt.
     * Beállítja a játékosok színét és nevét, valamint a győzelemhez szükséges
     * pontszámot. A konstruktor automatikusan betölti az első pályát.
     */
    GameManager();

    /**
     * @brief A GameManager osztály másoló konstruktora.
     * 
     * A másoló konstruktor megakadályozza a GameManager példányok másolását,
     * mivel a játékmenet egyedi példányt igényel.
     */
    GameManager(const GameManager& gameManager);

    /**
     * @brief A GameManager osztály másoló hozzárendelő operátora.
     * 
     * A másoló hozzárendelő operátor megakadályozza a GameManager példányok
     * hozzárendelését, mivel a játékmenet egyedi példányt igényel.
     */
    GameManager& operator=(const GameManager& gameManager);

    /**
     * @brief Ellenőrzi a játékosok állapotát és kezeli a győzelmet.
     * 
     * A metódus ellenőrzi, hogy valamelyik játékos meghalt-e. Ha egy játékos
     * meghal, a másik játékos pontszáma növekszik, és elindul az újraindítási
     * folyamat. Ha valamelyik játékos eléri a győzelemhez szükséges pontszámot,
     * a játék új pályára vált, és megjeleníti a győztes nevét.
     */
    void checkForWin();

    /**
     * @brief Kezeli az újraindítási folyamat visszaszámlálását.
     * 
     * A metódus csökkenti a `timeUntilReset` értékét a játék frissítési
     * ciklusai alapján. Ha az érték eléri a nullát, újraindítja a játékot.
     */
    void countReset();

    /**
     * @brief Visszaállítja a játék állapotát egy új körhöz.
     * 
     * A metódus visszaállítja a játékosok pozícióját és állapotát, növeli
     * a győztes játékos pontszámát, és ellenőrzi, hogy elérte-e a győzelemhez
     * szükséges pontszámot. Ha igen, a játék új pályára vált.
     */
    void resetGame();

    /**
     * @brief Visszaadja a jelenlegi pálya indexét.
     * 
     * A metódus visszaadja a jelenleg aktív pálya indexét, amelyet a
     * `MapManager` kezel. Ez az index határozza meg, hogy melyik pálya
     * van betöltve a játékban.
     * 
     * @return A jelenlegi pálya indexe.
     */
    size_t getMapId() const;

    /**
     * @brief A következő pálya számának meghatározása.
     * 
     * A metódus a jelenlegi pálya indexét növeli, és betölti a következő pályát
     * a `MapManager` segítségével. Ha nincs több elérhető pálya, a metódus
     * visszatér az első pályára.
     */
    void nextMap();

    public:
    /**
     * @brief Singleton minta megvalósítása.
     * 
     * A metódus biztosítja, hogy csak egy példány létezzen a `GameManager`
     * osztályból. Ha a példány még nem létezik, létrehozza azt.
     * 
     * @return A `GameManager` osztály egyetlen példánya.
     */
    static GameManager& getInstance();

    /**
     * @brief A `GameManager` osztály példánya erőforrásainak felszabadítása.
     * 
     * A metódus biztosítja, hogy a `GameManager` osztály példánya és
     * az összes kapcsolódó erőforrás felszabaduljon, amikor a játék
     * befejeződik
     */
    void shutDown();

    /**
     * @brief A játékmenet frissítése.
     * 
     * A metódus a játék főciklusában kerül meghívásra. Ellenőrzi a játékosok
     * halálát, szükség esetén növeli a győztes pontszámát, és elindítja az
     * újraindítási folyamatot. Ha a győzelemhez szükséges pontszámot elérte
     * valamelyik játékos, a játék új pályára vált.
     */
    void update() override;

    /**
     * @brief Visszaadja a jelenleg betöltött pálya szélességét.
     *
     * @return A pálya szélessége.
     */
    double getMapWidth() const;

    /**
     * @brief Visszaadja a jelenleg betöltött pálya magasságát.
     *
     * @return A pálya magassága.
     */
    double getMapHeight() const;
>>>>>>> a04c523 (Idk :3)
};
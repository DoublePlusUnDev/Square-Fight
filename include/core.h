#pragma once

#include <set>

/**
 * @brief Az objektumok frissítési sorrendjét meghatározó prioritások.
 * 
 * Az `UpdatePriority` enum az objektumok frissítési sorrendjét határozza meg
 * a játék főciklusában. A kisebb értékű prioritások előbb kerülnek frissítésre.
 * 
 * @var UpdatePriority::GAME_LOGIC
 *      A játék logikájának frissítése.
 * @var UpdatePriority::PLAYER_RENDERER
 *      A játékos megjelenítésének frissítése.
 * @var UpdatePriority::WALL_RENDERER
 *      A falak megjelenítésének frissítése.
 * @var UpdatePriority::UI_RENDERER
 *      A felhasználói felület megjelenítésének frissítése.
 * @var UpdatePriority::OTHER
 *      Minden más frissítése.
 * 
 */
enum class UpdatePriority : int
{
    GAME_LOGIC,
    PLAYER_RENDERER,
    WALL_RENDERER,
    UI_RENDERER,
    OTHER,
};

/**
 * @brief Az updatelhető objektumokat reprezentáló osztály.
 * 
 * Az `Updatable` osztály azokat az objektumokat reprezentálja, amelyek
 * frissíthetőek a játék főciklusában. Az osztályból származtatott
 * objektumok implementálják az `update()` metódust, amely a frissítést végzi.
 * 
 * Az osztály tárolja az objektum frissítési prioritását, amely alapján
 * a `GameRuntime` osztály rendezni tudja az `Updatable` objektumokat.
 */
class Updatable
{
    private:
    UpdatePriority priority; ///< Az updatelés prioritása.

    public:
    /**
     * @brief Az Updatable osztály konstruktora.
     * @param priority Az updatelés prioritása.
     */
    Updatable(const UpdatePriority priority);
    /**
     * @brief Az Updatable osztály másoló konstruktora.
     */
    Updatable(const Updatable& updatable);
    /**
     * @brief Az Updatable osztály értékadó operátora.
     */
    Updatable& operator=(const Updatable& updatable);
    /**
     * @brief Az Updatable osztály destruktora.
     */
    virtual ~Updatable();

    /** 
     * @brief A frissítést végző virtuális metódus.
    */
    virtual void update() = 0;

    /**
     * @brief Két updatelhető objektum prioritásának összehasonlító osztálya.
     */
    class Compare
    {
        public:
        bool operator()(const Updatable* updatable1, const Updatable* updatable2) const;
    };
};

/**
 * @brief A fizikai frissítést végző objektumokat reprezentáló osztály.
 * 
 * A `PhysicsUpdatable` osztály azokat az objektumokat reprezentálja, amelyek
 * fizikai frissítést végeznek a játék főciklusában. Az osztályból származtatott
 * objektumok implementálják a `physicsUpdate()` metódust, amely a fizikai
 * szimulációk frissítését végzi, például mozgás vagy ütközés számításokat.
 */
class PhysicsUpdatable
{
    public:
    /**
     * @brief A PhysicsUpdatable osztály konstruktora.
     */
    PhysicsUpdatable();
    /**
     * @brief A PhysicsUpdatable osztály másoló konstruktora.
     */
    PhysicsUpdatable(const PhysicsUpdatable& updatable);
    /**
     * @brief A PhysicsUpdatable osztály értékadó operátora.
     */
    PhysicsUpdatable& operator=(const PhysicsUpdatable& updatable);
    /**
     * @brief A PhysicsUpdatable osztály destruktora.
     */
    virtual ~PhysicsUpdatable();

    /**
     * @brief A fizikai frissítést végző virtuális metódus.
     */
    virtual void physicsUpdate() = 0;

    /**
     * @brief A normál frissítést követő metódus.
     * 
     * Lehetőséget biztosít a fizikai frissítést végző objektumok számára,
     * hogy a normál frissítést követően végezzenek el további
     * műveleteket, például a címkék eltűntetését.
     */
    virtual void postUpdate() = 0;
}; 

#ifndef CPORTA
struct SDL_Window;
struct SDL_Renderer;

/**
 * @brief A játék futását kezelő osztály.
 * 
 * A `GameRuntime` osztály felelős a játék futásának kezeléséért. Az osztály
 * inicializálja a játék futásához szükséges komponenseket, például az SDL
 * rendszert, az ablakot és a renderelőt. A főciklus során frissíti az
 * `Updatable` és `PhysicsUpdatable` objektumokat, kezeli a felhasználói
 * eseményeket, és biztosítja a megjelenítést.
 * 
 * Az osztály statikus metódusokon keresztül kezeli a játék futását, például
 * az inicializálást, a főciklus indítását és a játék leállítását.
 */
class GameRuntime
{
    private:
    static SDL_Window* SDLWindow; ///< SDL ablak.
    static SDL_Renderer* SDLRenderer; ///< SDL renderer.

    static bool running; ///< A játék futásának állapota.

    static unsigned long long lastFrameCounter; ///< Az utolsó képkocka frissítési ideje.
    static unsigned long long currentFrameCounter; ///< A jelenlegi képkocka frissítési ideje.
    
    static double deltaTime; ///< A játék legutóbbi képkockájához kirajzolásához szükséges idő.
    static double physicsSimTime; ///< A fizikai szimulációk között eltelt idő.

    static double targetFrameRate; ///< A maximális frissítési ráta.
    static double targetPhysicsRate; ///< A fizikai szimulációk rátája.

    static std::set<Updatable*, Updatable::Compare> updatables; ///< A képkockánként frissítendő objektumok.
    static std::set<PhysicsUpdatable*> physicsUpdatables; ///< A fizikai frissítést igénylő objektumok.

    /**
     * @brief A játék főciklusának futtatása.
     * 
     * A főciklusban a játék frissítése, a fizikai frissítés, a felhasználói
     * események kezelése, a megjelenítés és a frissítési idő számolása történik.
     */
    static void loop();
    
    /**
     * @brief A játék frissítése.
     * 
     * A játék frissítése során a képkockánként frissítendő objektumok
     * frissítése történik.
     */
    static void callUpdates();

    /**
     * @brief A fizikai frissítést igénylő objektumok frissítése.
     * 
     * A fizikai frissítést igénylő objektumok frissítése történik.
     */
    static void schedulePhysicsUpdates();
    
    public:
    /**
     * @brief A játék futásának inicializálása.
     * 
     * Az inicializálás során inicializálásra kerül az SDL rendszer, a játék ablaka
     * és a renderelő. Ha bármelyik komponens inicializálása sikertelen, a metódus
     * hamis értékkel tér vissza. 
     * 
     * @param resolutionX Az ablak szélessége pixelben.
     * @param resolutionY Az ablak magassága pixelben.
     * @return true, ha az inicializáció sikeres, különben false.
     */
    static bool init(const int resolutionX, const int resolutionY);

    /**
     * @brief A játék főciklusának elindítása.
     * 
     * A főciklus során a játék frissítése, a fizikai frissítés, a felhasználói
     * események kezelése és a megjelenítés történik. A ciklus addig fut, amíg
     * a `running` állapot igaz.
     */
    static void startGameLoop();

    /**
     * @brief A játék futásának befejezése.
     * 
     * A játék futásának leállítása során felszabadításra kerülnek a játék futásához
     * szükséges erőforrások, például az SDL ablak és a renderelő.
     */
    static void quit();

    /**
     * @brief Az SDL renderer lekérdezése.
     * @return Az SDL renderer.
     */
    static SDL_Renderer* getSDLRenderer();

    /**
     * @brief A játék lugtóbbi képkockájához kirajzolásához szükséges idő lekérdezése.
     * @return A játék legutóbbi képkockájához kirajzolásához szükséges idő.
     */
    static double getDeltaTime();

    /**
     * @brief A fizikai szimulációk között eltelt idő lekérdezése.
     * @return A fizikai szimulációk között eltelt idő.
     */
    static double getPhysicsDeltaTime();

    /**
     * Maximális frissítési ráta beállítása.
     * @param targetRate A maximális frissítési ráta.
     */
    static void setTargetFrameRate(const double targetRate);

    /**
     * Fizikai szimuláciák rátájának beállítása.
     * @param targetRate A fizikai szimulációk rátája.
     */
    static void setTargetPhysicsRate(const double targetRate);

    /**
     * @brief Az updatelhető objektum regisztrálása az updateléshez.
     * @param updatable Az updatelhető objektum.
     */
    static void registerForUpdate(Updatable* const updatable);

    /**
     * @brief Az updatelhető objektum eltávolítása az updatelésből.
     * @param updatable Az updatelhető objektum.
     */
    static void unregisterForUpdate(Updatable* const updatable);

    /**
     * @brief A fizikai frissítést végző objektum regisztrálása.
     * @param updatable A fizikai frissítést végző objektum.
     */
    static void registerForUpdate(PhysicsUpdatable* const updatable);

    /**
     * @brief A fizikai frissítést végző objektum eltávolítása.
     * @param updatable A fizikai frissítést végző objektum.
     */
    static void unregisterForUpdate(PhysicsUpdatable* const updatable);
};
#endif // CPORTA

#ifdef CPORTA

/**
 * @brief A játék futását kezelő osztály tesztelési célokra.
 */
class GameRuntime
{
    static std::set<Updatable*, Updatable::Compare> updatables; ///< A képkockánként frissítendő objektumok.
    static std::set<PhysicsUpdatable*> physicsUpdatables; ///< A fizikai frissítést igénylő objektumok.

    static double deltaTime; ///< A játék legutóbbi képkockájához kirajzolásához szükséges idő.

    static double targetFrameRate; ///< A maximális frissítési ráta.
    static double targetPhysicsRate; ///< A fizikai szimulációk rátája.

    public:
    /**
     * * @brief A játék tesztelési célú inicializálása.
     */
    static void configureMock(const double targetFrameRate, const double targetPhysicsRate);

    /**
     * @brief A játék főciklusának tesztelése.
     * 
     * @param calls A hívások száma.
     */
    static void mockUpdate(const size_t calls);

    /**
     * @brief A fizikai frissítést végző objektumok tesztelése.
     * 
     * @param calls A hívások száma.
     */
    static void mockPhysicsUpdate(const size_t calls);

    /**
     * @brief A játék lugtóbbi képkockájához kirajzolásához szükséges idő lekérdezése.
     * @return A játék legutóbbi képkockájához kirajzolásához szükséges idő.
     */
    static double getDeltaTime();

    /**
     * @brief A fizikai szimulációk között eltelt idő lekérdezése.
     * @return A fizikai szimulációk között eltelt idő.
     */
    static double getPhysicsDeltaTime();

    /**
     * Maximális frissítési ráta beállítása.
     * @param targetRate A maximális frissítési ráta.
     */
    static void setTargetFrameRate(const double targetRate);

    /**
     * Fizikai szimuláciák rátájának beállítása.
     * @param targetRate A fizikai szimulációk rátája.
     */
    static void setTargetPhysicsRate(const double targetRate);

    /**
     * @brief Az updatelhető objektum regisztrálása az updateléshez.
     * @param updatable Az updatelhető objektum.
     */
    static void registerForUpdate(Updatable* const updatable);

    /**
     * @brief Az updatelhető objektum eltávolítása az updatelésből.
     * @param updatable Az updatelhető objektum.
     */
    static void unregisterForUpdate(Updatable* const updatable);

    /**
     * @brief A fizikai frissítést végző objektum regisztrálása.
     * @param updatable A fizikai frissítést végző objektum.
     */
    static void registerForUpdate(PhysicsUpdatable* const updatable);

    /**
     * @brief A fizikai frissítést végző objektum eltávolítása.
     * @param updatable A fizikai frissítést végző objektum.
     */
    static void unregisterForUpdate(PhysicsUpdatable* const updatable);
};

#endif // CPORTA
#pragma once

#include "core.h"
#include "transform.h"
#include "colors.h"

/**
 * @brief A játék grafikai megjelenítéséért felelős osztály.
 * 
 * A `Renderer` osztály felelős a játék grafikai elemeinek megjelenítéséért,
 * beleértve a háttér kirajzolását, a képernyő és a játék világának koordinátái
 * közötti átváltást, valamint a játék világának méretének és arányainak kezelését.
 */
class Renderer : public Transform, Updatable
{
    private:
    static double gameHeight; ///< A játék világának magassága játékegységekben.
    static Color backgroundColor; //< A játék világának háttérszíne (RGBA formátumban).

    static Vector2 cameraOffset;
    static double cameraScale;

    public:
    /**
     * @brief Létrehoz egy `Renderer` objektumot.
     * 
     * Inicializálja a rendereléshez szükséges transzformációkat és prioritásokat.
     * 
     * @param transform Az objektum pozíciója és mérete.
     * @param priority Az objektum frissítési prioritása.
     */
    Renderer(const Transform& transform, UpdatePriority priority);

    /**
     * @brief Kirajzolja a játék hátterét.
     * 
     * A metódus a beállított háttérszínt használva kirajzolja a játék hátterét.
     */
    static void drawBackground();

    /**
     * @brief Visszaadja a játék világának szélességét.
     * 
     * A szélesség a játék világának magassága és a képarány alapján kerül kiszámításra.
     * 
     * @return A játék világának szélessége játékegységekben.
     */
    static double getGameWidth();
    
    /**
     * @brief Visszaadja a játék világának magasságát.
     * 
     * @return A játék világának magassága.
     */
    static double getGameHeight();

    /**
     * @brief Visszaadja a képernyő szélességét.
     * 
     * @return A képernyő szélessége pixelben.
     */
    static int getScreenWidth();

    /**
     * @brief Visszaadja a képernyő magasságát.
     * 
     * @return A képernyő magassága pixelben.
     */
    static int getScreenHeight();
    
    /**
     * @brief Visszaadja a képernyő képarányát.
     * 
     * Az arány a képernyő szélessége és magassága közötti hányados.
     * 
     * @return A képernyő képaránya.
     */
    static double getAspectRatio();
    
    /**
     * @brief Visszaadja a játék világának és a képernyőnek az arányát.
     * 
     * Az arány megmutatja, hogy a játék világának egy egysége hány pixelnek felel meg a képernyőn.
     * 
     * @return A játék világának és a képernyőnek az aránya.
     */
    static double getGameToScreenRatio();

    /**
     * @brief Visszaadja a képernyő és a játék világának arányát.
     * 
     * Az arány megmutatja, hogy a képernyő egy pixelje hány egységnek felel meg a játék világában.
     * 
     * @return A képernyő és a játék világának aránya.
     */
    static double getScreenToGameRatio();

    /**
     * @brief Átváltja a játék világának X koordinátáját képernyő koordinátára.
     * 
     * @param gameXPos A játék világának X koordinátája.
     * @return Az X koordináta pixelben.
     */
    static int gameToScreenXPos(const double gameXPos);

    /**
     * @brief Átváltja a játék világának Y koordinátáját képernyő koordinátára.
     * 
     * @param gameYPos A játék világának Y koordinátája.
     * @return Az Y koordináta pixelben.
     */
    static int gameToScreenYPos(const double gameYPos);

    /**
     * @brief Átváltja a képernyő X koordinátáját a játék világának koordinátájára.
     * 
     * @param screenXPos A képernyő X koordinátája pixelben.
     * @return Az X koordináta a játék világában.
     */
    static double screenToGameXPos(const int screenXPos);

    /**
     * @brief Átváltja a képernyő Y koordinátáját a játék világának koordinátájára.
     * 
     * @param screenYPos A képernyő Y koordinátája pixelben.
     * @return Az Y koordináta a játék világában.
     */
    static double screenToGameYPos(const int screenYPos);

    /**
     * @brief Beállítja a játék világának magasságát.
     * 
     * A magasság beállítása után a szélesség automatikusan kiszámításra kerül az arány alapján.
     * 
     * @param gameHeight A játék világának új magassága.
     */
    static void setGameHeight(const double gameHeight);

    /**
     * @brief Beállítja a játék háttérszínét.
     * 
     * @param color Az új háttérszín.
     */
    static void setBackgroundColor(const Color color);

    /**
     * @brief Beálítja a játék kamerájának eltolását.
     * 
     * @param offset Az új eltolás vektora.
     */
    static void setCameraOffset(const Vector2& offset);
    
    /**
     * @brief Visszaadja a játék kamerájának méretét.
     * 
     * @param scale A kamera mérete.
     */
    static void setCameraScale(const double scale);
};
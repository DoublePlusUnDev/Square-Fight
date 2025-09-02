#pragma once
#include "memtrace.h"

#include "core.h"
#include "colors.h"

#include <SDL3_ttf/SDL_ttf.h>
#include <string>

/**
 * @brief Szövegek kezelésére és megjelenítésére szolgáló osztály.
 * 
 * A `TextHandler` osztály felelős a játékban megjelenített szövegek kezeléséért,
 * beleértve a szövegek megjelenítését, elrejtését, valamint a szín és méret
 * dinamikus beállítását. Az osztály az SDL_ttf könyvtárat használja a szövegek
 * rendereléséhez, és automatikusan alkalmazkodik a képernyő méretéhez.
 */
class TextHandler : Updatable
{
    std::string text; ///< A képernyőn megjelenítendő szöveg tartalma.
    Color color; ///< A szöveg megjelenítéséhez használt szín (RGBA formátumban).
    double textScale = 0.2; ///< A szöveg méretének aránya a képernyő magasságához viszonyítva.
    bool shouldDisplay; ///< Jelzi, hogy a szöveg megjelenjen-e.
    TTF_Font* font; ///< Az aktuálisan betöltött betűtípus.
    
    int lastScreenHeight; ///< Az utolsó ismert képernyőmagasság, a szöveg méretezéséhez.

    /**
     * @brief A szöveg renderelése a képernyő közepére.
     * 
     * A metódus a megadott szöveget és színt rendereli a képernyő közepére
     * az aktuális betűtípus, méret és képernyőméret alapján. Automatikusan
     * újratölti a betűtípust, ha a képernyő mérete megváltozik.
     */
    void renderText();

    /**
     * @brief Betölti a betűtípust a megadott mérettel.
     * 
     * A metódus az SDL_ttf könyvtár segítségével betölti a betűtípust, amelyet
    * a szöveg rendereléséhez használ. Ha a betűtípus betöltése sikertelen,
    * hibaüzenetet ír a naplóba.
     * 
     * @param fontSize A betűtípus mérete.
     */
    void loadFont(const double fontSize);

    /**
     * @brief Felszabadítja a betöltött betűtípust.
     * 
     * A metódus felszabadítja az aktuálisan betöltött betűtípushoz tartozó
     * erőforrásokat.
     */
    void unloadFont();

    public:
    /**
     * @brief Létrehoz egy `TextHandler` objektumot.
     * 
     * Inicializálja az osztály tagváltozóit, és előkészíti a szövegkezelést.
     */
    TextHandler();

    /**
     * @brief Felszabadítja a `TextHandler` által használt erőforrásokat.
     * 
     * A destruktor felszabadítja a betöltött betűtípushoz tartozó erőforrásokat,
     * és biztosítja, hogy ne maradjanak memória-szivárgások.
     */
    ~TextHandler();

    /**
     * @brief A szövegkezelő frissítése a játék főciklusában.
     * 
     * A metódus ellenőrzi a képernyő méretének változását, és ha szükséges,
     * újratölti a betűtípust és újrarendereli a szöveget.
     */
    void update() override;

    /**
     * @brief Szöveg megjelenítése a képernyőn.
     * 
     * A metódus beállítja a megjelenítendő szöveget és annak színét, majd
     * megjeleníti azt a képernyőn.
     * 
     * @param text A megjelenítendő szöveg.
     * @param color A szöveg színe.
     */
    void displayText(const std::string& text, const Color& color);

    /**
     * @brief Elrejti a képernyőn megjelenített szöveget.
     * 
     * A metódus eltünteti a jelenleg megjelenített szöveget a képernyőről.
     */
    void hideText();

    /**
     * @brief A szövegkezelő erőforrásainak felszabadítása.
     * 
     * A metódus felszabadítja a `TextHandler` által használt erőforrásokat,
     * ezalatt a betűtípust értve.
     */
    void cleanUp();
};
#pragma once

#include <SDL3/SDL.h>

/**
 * @brief Egy játékoshoz tartozó billentyűkiosztásokat reprezentáló osztály.
 * 
 * Az `InputScheme` osztály a játékoshoz tartozó billentyűkiosztásokat
 * reprezentálja. Az osztály tárolja a játékos által használt billentyűk
 * kódjait, például az ugrás, mozgás és speciális műveletek vezérléséhez.
 * Lehetővé teszi a billentyűkódok lekérdezését, amelyeket a játék
 * bemeneti kezelője használhat.
 */
class InputScheme
{
    private:
    SDL_Keycode jumpKey; ///< A játékos ugrásához használt billentyű kódja (SDL key code).
    SDL_Keycode leftKey; ///< A játékos balra mozgásához használt billentyű kódja (SDL key code).
    SDL_Keycode dashKey; ///< A játékos "lefelé vetődés"-hez használt billentyű kódja (SDL key code).
    SDL_Keycode rightKey; ///< A játékos jobbra mozgásához használt billentyű kódja (SDL key code).

    public:
    /**
     * @brief Konstruktor.
     * 
     * Inicializálja az `InputScheme` objektumot a megadott billentyűkódokkal.
     * A billentyűkódok az SDL által definiált key code-ok, amelyek a játékos
     * különböző műveleteit vezérlik, például ugrás, mozgás és speciális akciók.
     * 
     * @param jumpKey A játékos ugrásához használt billentyű kódja (SDL key code).
     * @param leftKey A játékos balra mozgásához használt billentyű kódja (SDL key code).
     * @param dashKey A játékos "lefelé vetődés"-hez használt billentyű kódja (SDL key code).
     * @param rightKey A játékos jobbra mozgásához használt billentyű kódja (SDL key code).
     */
    InputScheme(const SDL_Keycode jumpKey, const SDL_Keycode leftKey, const SDL_Keycode dashKey, const SDL_Keycode rightKey);

    /**
     * @brief Visszaadja a játékos ugrásához használt billentyű kódját.
     * 
     * A metódus visszaadja az SDL által definiált key code-ot, amely a játékos
     * ugrásának vezérlésére szolgál.
     * 
     * @return A játékos ugrásához használt billentyű kódja.
     */
    SDL_Keycode getJumpKey() const;

    /**
     * @brief Visszaadja a játékos balra mozgásához használt billentyű kódját.
     * 
     * A metódus visszaadja az SDL által definiált key code-ot, amely a játékos
     * balra mozgásának vezérlésére szolgál.
     * 
     * @return A játékos balra mozgásához használt billentyű kódja.
     */
    SDL_Keycode getLeftKey() const;

    /**
     * @brief Visszaadja a játékos "lefelé vetődés"-hez használt billentyű kódját.
     * 
     * A metódus visszaadja az SDL által definiált key code-ot, amely a játékos
     * "lefelé vetődés" műveletének vezérlésére szolgál.
     * 
     * @return A játékos "lefelé vetődés"-hez használt billentyű kódja.
     */
    SDL_Keycode getDashKey() const;

    /**
     * @brief Visszaadja a játékos jobbra mozgásához használt billentyű kódját.
     * 
     * A metódus visszaadja az SDL által definiált key code-ot, amely a játékos
     * jobbra mozgásának vezérlésére szolgál.
     * 
     * @return A játékos jobbra mozgásához használt billentyű kódja.
     */
    SDL_Keycode getRightKey() const;
};
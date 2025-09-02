#pragma once

#include <SDL3/SDL.h>
#include <unordered_set>

/**
 * @brief A felhasználói bemenetek kezelésére szolgáló osztály.
 * 
 * Az `InputHandler` osztály felelős a felhasználói bemenetek, például
 * billentyűleütések és billentyűfelengedések kezeléséért. Az osztály
 * nyomon követi a lenyomott billentyűket, és lehetővé teszi azok állapotának
 * gyors lekérdezését.
 */
class InputHandler
{
    private:
    /**
     * @brief Az aktuálisan lenyomott billentyűk kódjait tároló halmaz.
     * 
     * A `pressedKeys` halmaz az SDL események alapján frissül, és tartalmazza
     * az összes olyan billentyű kódját, amely jelenleg lenyomott állapotban van.
     * Ez lehetővé teszi a billentyűk állapotának gyors és hatékony lekérdezését.
     */
    static std::unordered_set<SDL_Keycode> pressedKeys;

    public:
    /**
     * @brief Kezeli a felhasználói bemenetekhez tartozó SDL eseményeket.
     * 
     * A metódus az SDL események alapján frissíti a `pressedKeys` halmazt.
     * Billentyűleütés esetén hozzáadja a billentyű kódját a halmazhoz,
     * míg billentyűfelengedés esetén eltávolítja azt.
     * 
     * @param event Az SDL esemény, amely tartalmazza a felhasználói bemenetet.
     */
    static void handleEvent(SDL_Event& event);

    /**
     * @brief A billentyűk állapotának lekérdezése.
     * 
     * A metódus ellenőrzi, hogy a megadott billentyű kódja szerepel-e a
     * `pressedKeys` halmazban. Ha a billentyű lenyomva van, igaz értéket ad
     * vissza, különben hamisat.
     * 
     * @param key A billentyű kódja, amelynek állapotát le kell kérdezni.
     * @return true, ha a billentyű lenyomva van, különben false.
     */
    static bool isKeyPressed(SDL_Keycode key);
};
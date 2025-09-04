#pragma once

#include "renderer.h"

/**
 * @brief Egy egyszínű téglalapot kirajzoló objektum.
 * 
 * A `BoxRenderer` osztály felelős egy téglalap alakú objektum kirajzolásáért
 * a megadott színnel és mérettel. Az osztály a `Renderer` osztályból származik,
 * és annak frissítési mechanizmusát használja a téglalap megjelenítéséhez.
 * 
 * Használható statikus vagy dinamikus objektumok kirajzolására a játék világában.
 */
class BoxRenderer : public Renderer
{
    private:
    Color color; ///< Az objektum által kirajzolt téglalap színe (RGBA formátumban).

    public:
    /**
     * @brief Létrehoz egy BoxRenderer objektumot.
     * 
     * Létrehoz egy téglalapot kirajzoló objektumot, amely a megadott helyzetben,
     * méretben és színnel jelenik meg. Az objektum frissítési prioritása
     * meghatározza, hogy milyen sorrendben kerül frissítésre más renderelő
     * objektumokhoz képest.
     * 
     * @param transform Az objektum helyzete és mérete.
     * @param color Az objektum színe.
     * @param priority Az objektum update prioritása.
     */
    BoxRenderer(const Transform& transform, const Color& color, const UpdatePriority priority);

    /**
     * @brief Végrehatja a téglalap frissítését.
     * 
     * A metódus kiszámítja a téglalap képernyőn megjelenő pozícióját és méretét
     * a `Transform` adatai alapján, majd a megadott színnel kirajzolja azt az SDL
     * renderelő segítségével.
     */
    void update() override;
};
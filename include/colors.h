#pragma once

#ifndef CPORTA
#include <SDL3/SDL_pixels.h>
#else
struct SDL_Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};
#endif

/**
 * @brief Az SDL_Color egyszerűsített aliasa.
 * 
 * A `Color` típus az SDL által definiált `SDL_Color` struktúra aliasa,
 * amely RGBA színértékeket tárol.
 */
using Color = SDL_Color;

/**
 * @brief Létrehoz egy új színt a megadott RGB értékekkel.
 * 
 * A függvény egy `Color` objektumot hoz létre a megadott vörös (R),
 * zöld (G) és kék (B) színintenzitások alapján. Az alfa (A) érték
 * alapértelmezés szerint 255, ami teljesen átlátszatlan színt jelent.
 * 
 * @param r A vörös szín intenzitása (0–255).
 * @param g A zöld szín intenzitása (0–255).
 * @param b A kék szín intenzitása (0–255).
 * @return Az új szín `Color` típusban.
 */
Color makeColor(const unsigned char r, const unsigned char g, const unsigned char b);

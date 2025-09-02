#include "colors.h"

Color makeColor(const unsigned char r, const unsigned char g, const unsigned char b)
{
    return SDL_Color{r, g, b, 255};
}
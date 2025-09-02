#ifndef CPORTA

#include "inputscheme.h"

InputScheme::InputScheme(const SDL_Keycode jumpKey, const SDL_Keycode leftKey, const SDL_Keycode dashKey, const SDL_Keycode rightKey)
: jumpKey(jumpKey), leftKey(leftKey), dashKey(dashKey), rightKey(rightKey)
{

}

SDL_Keycode InputScheme::getJumpKey() const { return jumpKey; }
SDL_Keycode InputScheme::getLeftKey() const { return leftKey; }
SDL_Keycode InputScheme::getDashKey() const { return dashKey; }
SDL_Keycode InputScheme::getRightKey() const { return rightKey; }

#endif // CPORTA
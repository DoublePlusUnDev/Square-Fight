#ifndef CPORTA
#include "inputhandler.h"

std::unordered_set<SDL_Keycode> InputHandler::pressedKeys{std::unordered_set<SDL_Keycode>()};

void InputHandler::handleEvent(SDL_Event& event)
{
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        pressedKeys.insert(event.key.key);
    }
    else if (event.type == SDL_EVENT_KEY_UP)
    {
        pressedKeys.erase(event.key.key);
    }
}

bool InputHandler::isKeyPressed(SDL_Keycode key)
{
    return pressedKeys.count(key);
}
#endif // CPORTA
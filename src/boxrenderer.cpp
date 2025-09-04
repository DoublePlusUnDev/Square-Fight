<<<<<<< HEAD
#ifndef CPORTA
#include "boxrenderer.h"

#include <SDL3/SDL.h>

BoxRenderer::BoxRenderer(const Transform& transform, const Color& color, const UpdatePriority priority) 
: Renderer(transform, priority), color(color)
{

}

void BoxRenderer::update()
{
    SDL_FRect rect;
    //width and height length
    rect.w = getScale().x * getGameToScreenRatio();
    rect.h = getScale().y * getGameToScreenRatio();
    //top left corner
    rect.x = gameToScreenXPos(getPosition().x) - rect.w / 2;
    rect.y = gameToScreenYPos(getPosition().y) - rect.h / 2;

    SDL_SetRenderDrawColor(GameRuntime::getSDLRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(GameRuntime::getSDLRenderer(), &rect);
}
=======
#ifndef CPORTA
#include "boxrenderer.h"

#include <SDL3/SDL.h>

BoxRenderer::BoxRenderer(const Transform& transform, const Color& color, const UpdatePriority priority) 
: Renderer(transform, priority), color(color)
{

}

void BoxRenderer::update()
{
    SDL_FRect rect;
    //width and height length
    rect.w = getScale().x * getGameToScreenRatio();
    rect.h = getScale().y * getGameToScreenRatio();
    //top left corner
    rect.x = gameToScreenXPos(getPosition().x) - rect.w / 2;
    rect.y = gameToScreenYPos(getPosition().y) - rect.h / 2;

    SDL_SetRenderDrawColor(GameRuntime::getSDLRenderer(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(GameRuntime::getSDLRenderer(), &rect);
}
>>>>>>> a04c523 (Idk :3)
#endif
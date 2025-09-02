#ifndef CPORTA
#include "renderer.h"

#include <SDL3/SDL.h>

double Renderer::gameHeight = 5;
Color Renderer::backgroundColor = makeColor(255, 255, 255);
Vector2 Renderer::cameraOffset = Vector2(0, 0);
double Renderer::cameraScale = 1;

Renderer::Renderer(const Transform& transform, const UpdatePriority priority)
: Transform(transform), Updatable(priority)
{

}

void Renderer::drawBackground()
{
    SDL_SetRenderDrawColor(GameRuntime::getSDLRenderer(), backgroundColor.r, backgroundColor.g, backgroundColor.b, 0xff);
    SDL_RenderClear(GameRuntime::getSDLRenderer());
}

double Renderer::getGameWidth()
{
    return getGameHeight() * getAspectRatio();
}

double Renderer::getGameHeight()
{
    return gameHeight * cameraScale;
}

int Renderer::getScreenWidth()
{
    int width, height;
    SDL_GetCurrentRenderOutputSize(GameRuntime::getSDLRenderer(), &width, &height);
    return width;
}

int Renderer::getScreenHeight() 
{
    int width, height;
    SDL_GetCurrentRenderOutputSize(GameRuntime::getSDLRenderer(), &width, &height);
    return height;
}

double Renderer::getAspectRatio()
{
    return (double) getScreenWidth() / (double) getScreenHeight();
}

double Renderer::getGameToScreenRatio()
{
    return (double)getScreenHeight() / (2 * getGameHeight());
}

double Renderer::getScreenToGameRatio()
{
    return 2 * getGameHeight() / (double)getScreenHeight();
}

int Renderer::gameToScreenXPos(const double gameXPos)
{
    return getScreenWidth() / 2 + int((gameXPos - cameraOffset.x) * getGameToScreenRatio());
}

int Renderer::gameToScreenYPos(const double gameYPos)
{
    return getScreenHeight() / 2 - int((gameYPos + cameraOffset.y) * getGameToScreenRatio());
}

double Renderer::screenToGameXPos(const int screenXPos)
{
    return ((double)screenXPos - (double)getScreenWidth() / 2) * getScreenToGameRatio() + cameraOffset.x;
}

double Renderer::screenToGameYPos(const int screenYPos)
{
    return - ((double)screenYPos - (double)getScreenHeight() / 2) * getScreenToGameRatio() - cameraOffset.y;
}

void Renderer::setGameHeight(const double gameHeight)
{
    Renderer::gameHeight = gameHeight;
}

void Renderer::setBackgroundColor(const Color backgroundColor)
{
    Renderer::backgroundColor = backgroundColor;
}

void Renderer::setCameraOffset(const Vector2& cameraOffset)
{
    Renderer::cameraOffset = cameraOffset;
}

void Renderer::setCameraScale(const double cameraScale)
{
    Renderer::cameraScale = cameraScale;
}
#endif // CPORTA
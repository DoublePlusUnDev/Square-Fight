#ifndef CPORTA
#include "texthandler.h"

#include "renderer.h"

TextHandler::TextHandler()
: Updatable(UpdatePriority::UI_RENDERER), shouldDisplay(false), lastScreenHeight(0)
{
    loadFont(1);
}

TextHandler::~TextHandler()
{
    unloadFont();
}

void TextHandler::loadFont(const double fontSize)
{
    font = TTF_OpenFont("gamefont.ttf", fontSize);

    if (font == nullptr)
    {
        SDL_Log("Failed to load font: %s", SDL_GetError());
    }
}

void TextHandler::unloadFont() 
{
    if (font != nullptr)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

void TextHandler::renderText()
{
    if (shouldDisplay == false) return; 

    int screenHeight = Renderer::getScreenHeight();
    if (screenHeight != lastScreenHeight)
    {
        unloadFont();

        loadFont(textScale * screenHeight);
        lastScreenHeight = screenHeight;
    }


    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), text.length(), color);
    if (textSurface == nullptr)
    {
        SDL_Log("Error creating text surface: %s", SDL_GetError());
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(GameRuntime::getSDLRenderer(), textSurface);
    if (textTexture == nullptr)
    {
        SDL_Log("Error creating text texture: %s", SDL_GetError());
        SDL_DestroySurface(textSurface);
        return;
    }

    float xCenter = (float)Renderer::getScreenWidth() / 2;
    float yCenter = (float)Renderer::getScreenHeight() / 2;
    float xScale = (float)textSurface->w;
    float yScale = (float)textSurface->h;
    SDL_FRect renderQuad = {xCenter - xScale / 2, yCenter - yScale / 2, xScale, yScale};

    SDL_DestroySurface(textSurface);
    
    SDL_RenderTexture(GameRuntime::getSDLRenderer(), textTexture, nullptr, &renderQuad);

    SDL_DestroyTexture(textTexture);
}

void TextHandler::update()
{
    renderText();
}

void TextHandler::displayText(const std::string& text, const Color& color)
{
    this->text = text;
    this->color = color;

    shouldDisplay = true;
}

void TextHandler::hideText()
{
    shouldDisplay = false;
}

void TextHandler::cleanUp()
{
    unloadFont();
}
#endif // CPORTA
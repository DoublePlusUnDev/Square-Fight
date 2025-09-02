#include "core.h"

#ifndef CPORTA
#include "renderer.h"
#include "inputhandler.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#endif

#include <algorithm>

#include "memtrace.h"

Updatable::Updatable(const UpdatePriority priority)
: priority(priority)
{
    GameRuntime::registerForUpdate(this);
}

Updatable::Updatable(const Updatable& updatable)
: priority(updatable.priority)
{
    GameRuntime::registerForUpdate(this);
}

Updatable& Updatable::operator=(const Updatable& updatable)
{
    GameRuntime::unregisterForUpdate(this);
    priority = updatable.priority;
    GameRuntime::registerForUpdate(this);
    return *this;
}

Updatable::~Updatable()
{
    GameRuntime::unregisterForUpdate(this);
}

PhysicsUpdatable::PhysicsUpdatable()
{
    GameRuntime::registerForUpdate(this);
}

PhysicsUpdatable::PhysicsUpdatable(const PhysicsUpdatable& updatable)
{
    GameRuntime::registerForUpdate(this);
}

PhysicsUpdatable& PhysicsUpdatable::operator=(const PhysicsUpdatable& updatable)
{
    return *this;
}

PhysicsUpdatable::~PhysicsUpdatable()
{
    GameRuntime::unregisterForUpdate(this);
}

bool Updatable::Compare::operator()(const Updatable* updatable1, const Updatable* updatable2) const
{
    if (updatable1->priority < updatable2->priority)
        return true;
    else if (updatable1->priority > updatable2->priority)
        return false;
    else
        return updatable1 < updatable2;
}

#ifndef CPORTA
SDL_Window* GameRuntime::SDLWindow = nullptr;
SDL_Renderer* GameRuntime::SDLRenderer = nullptr;

bool GameRuntime::running = false;

unsigned long long GameRuntime::lastFrameCounter {0};
unsigned long long GameRuntime::currentFrameCounter {0};

#endif
double GameRuntime::deltaTime = 0;
#ifndef CPORTA
double GameRuntime::physicsSimTime = 0;
#endif

double GameRuntime::targetFrameRate = 60;
double GameRuntime::targetPhysicsRate = 50;

std::set<Updatable*, Updatable::Compare> GameRuntime::updatables = std::set<Updatable*, Updatable::Compare>();
std::set<PhysicsUpdatable*> GameRuntime::physicsUpdatables = std::set<PhysicsUpdatable*>();

#ifndef CPORTA
void GameRuntime::loop()
{
    lastFrameCounter = currentFrameCounter;
    currentFrameCounter = SDL_GetPerformanceCounter();
    deltaTime = (double) ((currentFrameCounter - lastFrameCounter)/ (double)SDL_GetPerformanceFrequency());

    physicsSimTime += deltaTime;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        InputHandler::handleEvent(event);

        switch(event.type)
        {
            case SDL_EVENT_KEY_DOWN:
                if (event.key.key == SDLK_F11)
                {
                    bool isFullscreen = SDL_GetWindowFlags(SDLWindow) & SDL_WINDOW_FULLSCREEN;
                    SDL_SetWindowFullscreen(SDLWindow, isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
                }
                break;


            case SDL_EVENT_QUIT:
                SDL_Log("Game quit!");
                running = false;
                return;
        }
    }
    
    Renderer::drawBackground();
    schedulePhysicsUpdates();
    callUpdates();
    
    SDL_RenderPresent(SDLRenderer);
    SDL_Delay(1000 / targetFrameRate - deltaTime);
}

void GameRuntime::callUpdates()
{
    for (Updatable* updatable : updatables)
    {
        updatable->update();
    }

    for (PhysicsUpdatable* updatable : physicsUpdatables)
    {
        updatable->postUpdate();
    }
}

void GameRuntime::schedulePhysicsUpdates()
{
    while (physicsSimTime > getPhysicsDeltaTime())
    {
        for (PhysicsUpdatable* updatable : physicsUpdatables)
        {
            updatable->physicsUpdate();
        }
        physicsSimTime -= getPhysicsDeltaTime();
    }
}

bool GameRuntime::init(const int resolutionX, const int resolutionY)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == false)
    {
        SDL_Log("SDL failed to initialize: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() == false)
    {
        SDL_Log("SDL_ttf failed to initialize: %s", SDL_GetError());
        return false;
    }
    
    SDLWindow = SDL_CreateWindow("Platfomer Game", resolutionX, resolutionY, SDL_WINDOW_RESIZABLE);
    if (SDLWindow == NULL)
    {
        SDL_Log("SDL failed to create SDLWindow: %s", SDL_GetError());
        return false;
    }
    
    SDLRenderer = SDL_CreateRenderer(SDLWindow, NULL);
    if (SDLRenderer == NULL)
    {
        SDL_Log("SDL failed to create SDLRenderer: %s", SDL_GetError());
        return false;
    }
    SDL_Log("SDL3 intialized");

    return true;
}

void GameRuntime::startGameLoop()
{
    currentFrameCounter = SDL_GetPerformanceCounter();
    lastFrameCounter = 0;

    physicsSimTime = 0;

    running = true;
    while (running)
    {
        loop();
    }
}

void GameRuntime::quit()
{
    SDL_Log("SDL3 shut down!");
    SDL_DestroyRenderer(SDLRenderer);
    SDL_DestroyWindow(SDLWindow);
    TTF_Quit();
    SDL_Quit();
}

SDL_Renderer* GameRuntime::getSDLRenderer() { return SDLRenderer; }
#endif
double GameRuntime::getDeltaTime() { return deltaTime; }

double GameRuntime::getPhysicsDeltaTime() { return 1 / targetPhysicsRate; }

void GameRuntime::setTargetFrameRate(double targetRate) { targetFrameRate = targetRate; }

void GameRuntime::setTargetPhysicsRate(double targetRate) { targetPhysicsRate = targetRate; }

void GameRuntime::registerForUpdate(Updatable* const updatable)
{
    updatables.insert(updatable);
}

void GameRuntime::unregisterForUpdate(Updatable* const updatable)
{
    updatables.erase(updatable);
}

void GameRuntime::registerForUpdate(PhysicsUpdatable* const updatable)
{
    physicsUpdatables.insert(updatable);
}

void GameRuntime::unregisterForUpdate(PhysicsUpdatable* const updatable)
{
    physicsUpdatables.erase(updatable);
}

#ifdef CPORTA
void GameRuntime::configureMock(const double targetFrameRate, const double targetPhysicsRate)
{
    GameRuntime::targetFrameRate = targetFrameRate;
    GameRuntime::targetPhysicsRate = targetPhysicsRate;

    GameRuntime::deltaTime = 1 / targetFrameRate;
}

void GameRuntime::mockUpdate(const size_t calls)
{
    for (size_t i = 0; i < calls; i++)
    {
        for (Updatable* updatable : updatables)
        {
            updatable->update();
        }
    }

    for (PhysicsUpdatable* updatable : physicsUpdatables)
    {
        updatable->postUpdate();
    }
}

void GameRuntime::mockPhysicsUpdate(const size_t calls)
{
    for (size_t i = 0; i < calls; i++)
    {
        for (PhysicsUpdatable* updatable : physicsUpdatables)
        {
            updatable->physicsUpdate();
        }
    }
}
#endif
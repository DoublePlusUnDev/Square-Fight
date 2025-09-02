#ifndef CPORTA
#include "gamemanager.h"
#endif

#ifdef CPORTA
#include "test.h"
#endif

#include "memtrace.h"

int main() 
{ 
    //game behavior
    #ifndef CPORTA
    bool initSuccess = GameRuntime::init(1280, 720);
    GameRuntime::setTargetFrameRate(60);
    GameRuntime::setTargetPhysicsRate(100);

    if (initSuccess == false)
        return -1;

    
    //access singleton to initialize game manager and start game
    GameManager::getInstance();

    GameRuntime::startGameLoop();
    
    //free sdl resources before shutting sdl down
    GameManager::getInstance().shutDown();
    
    GameRuntime::quit();
    #endif

    //test behavior
    #ifdef CPORTA
    TestRunner::start();
    #endif

    return 0;
}
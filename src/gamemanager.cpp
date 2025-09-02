#ifndef CPORTA
#include "gamemanager.h"

#include <stdexcept>

GameManager::GameManager()
: Updatable(UpdatePriority::GAME_LOGIC), 
  textHandler(),
  mapManager(),
  player1(player1Color, InputScheme(SDLK_SPACE, SDLK_A, SDLK_S, SDLK_D)), 
  player2(player2Color, InputScheme(SDLK_RSHIFT, SDLK_LEFT, SDLK_DOWN, SDLK_RIGHT)),
  player1Score(0),
  player2Score(0),
  round(0),
  timeUntilReset(0),
  shouldReset(false)
{
    resetGame();

}

GameManager& GameManager::getInstance()
{
    static GameManager instance;
    return instance;
}

void GameManager::shutDown()
{
    textHandler.cleanUp();
    mapManager.unloadMap();
}

void GameManager::checkForWin()
{
    //player 2 is dead and player 1 is alive
    if (player1.isDead() && !player2.isDead())
    {
        player2Score++;
        shouldReset = true;
        timeUntilReset = resetTime;

        int scoreToWin = mapManager.getScoreToWin();

        if (player2Score >= scoreToWin)
        {
            textHandler.displayText(player2Name + " won!", player2Color);
        }
        else
        {
            textHandler.displayText(player2Name + " scored " + std::to_string(player2Score) + "/" + std::to_string(scoreToWin), player2Color);
        }
    }

    //player 1 is dead and player 2 is alive
    else if (player2.isDead() && !player1.isDead())
    {
        player1Score++;
        shouldReset = true;
        timeUntilReset = resetTime;
        
        int scoreToWin = mapManager.getScoreToWin();

        if (player1Score >= mapManager.getScoreToWin())
        {
            textHandler.displayText(player1Name + " won!", player1Color);
        }
        else
        {
            textHandler.displayText(player1Name + " scored " + std::to_string(player1Score) + "/" + std::to_string(scoreToWin), player1Color);
        }
    }

    //player 1 and player 2 both are dead
    else if (player1.isDead() && player2.isDead())
    {
        shouldReset = true;
        timeUntilReset = resetTime;
        textHandler.displayText("Tie", {100, 100, 100});
    }
}

void GameManager::countReset()
{
    if (timeUntilReset <= 0)
            resetGame();
        else
            timeUntilReset -= GameRuntime::getDeltaTime();
}

void GameManager::resetGame()
{
    shouldReset = false;
    textHandler.hideText();
    
    //load next map if one of the players won
    if (player1Score >= mapManager.getScoreToWin() || player2Score >= mapManager.getScoreToWin())
    {
        nextMap();
        player1Score = 0;
        player2Score = 0;
    }
    //load the current map again
    else
    {
        mapManager.loadMap(getMapId());
    }

    //rest player positions
    player1.reset(mapManager.getPlayerPosition(0));
    player2.reset(mapManager.getPlayerPosition(1));
}

size_t GameManager::getMapId() const
{
    return round % mapManager.getMapCount();
}

void GameManager::nextMap()
{
    round++;
    mapManager.loadMap(getMapId());    
}

void GameManager::update()
{
    if (!shouldReset)
    {
        checkForWin();
    }
    else
    {
        countReset();
    }
}

double GameManager::getMapWidth() const
{
    return mapManager.getMapHeight() * Renderer::getAspectRatio();
}

double GameManager::getMapHeight() const
{
    return mapManager.getMapHeight();
}
#endif // CPORTA
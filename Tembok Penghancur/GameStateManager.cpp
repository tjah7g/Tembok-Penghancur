// GameStateManager.cpp
#include "GameStateManager.h"

GameStateManager* GameStateManager::instance = nullptr;

GameStateManager::GameStateManager()
{
    reset();
}

GameStateManager* GameStateManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new GameStateManager();
    }
    return instance;
}

void GameStateManager::reset()
{
    win = false;
    lose = false;
    finalScore = 0;
}

void GameStateManager::setWin(bool value)
{
    win = value;
}

void GameStateManager::setLose(bool value)
{
    lose = value;
}

bool GameStateManager::getWin() const
{
    return win;
}

bool GameStateManager::getLose() const
{
    return lose;
}

void GameStateManager::setFinalScore(int score)
{
    finalScore = score;
}

int GameStateManager::getFinalScore() const
{
    return finalScore;
}

// GameStateManager.h
#pragma once

class GameStateManager
{
private:
    static GameStateManager* instance;
    bool win;
    bool lose;
    int finalScore;

    GameStateManager(); // private constructor

public:
    static GameStateManager* getInstance();

    void reset();

    void setWin(bool value);
    void setLose(bool value);

    bool getWin() const;
    bool getLose() const;

    void setFinalScore(int score);
    int getFinalScore() const;
};

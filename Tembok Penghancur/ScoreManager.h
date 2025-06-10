#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H
#ifdef _MSC_VER
#pragma once
#endif  
using namespace std;

class ScoreManager {
private:
    static ScoreManager* instance;
    int score;

    ScoreManager() : score(0) {}

public:
    static ScoreManager* getInstance() {
        if (!instance)
            instance = new ScoreManager();
        return instance;
    }

    void addScore(int value) {
        score += value;
    }

    int getScore() const {
        return score;
    }

    void resetScore() {
        score = 0;
    }
};

//ScoreManager* ScoreManager::instance = nullptr;

#endif
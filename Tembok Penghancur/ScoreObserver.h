#ifndef SCORE_OBSERVER_H
#define SCORE_OBSERVER_H

#include "Observer.h"
#include "ScoreManager.h"

class ScoreObserver : public Observer
{
public:
    void onNotify() override
    {
        ScoreManager::getInstance()->addScore(100);
    }
};

#endif

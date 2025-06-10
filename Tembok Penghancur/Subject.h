#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Observer.h"
#include <vector>

class Subject
{
protected:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* observer)
    {
        observers.push_back(observer);
    }

    void notifyAll()
    {
        for (Observer* observer : observers)
        {
            observer->onNotify();
        }
    }
};

#endif

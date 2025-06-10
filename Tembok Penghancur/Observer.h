#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
    virtual void onNotify() = 0;
    virtual ~Observer() = default;
};

#endif

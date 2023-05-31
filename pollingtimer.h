#ifndef POLLINGTIMER_H
#define POLLINGTIMER_H

#include <QObject>
#include <atomic>
#include <thread>

#include "command.h"

class PollingTimer
{
protected:
    std::atomic<bool> shouldRun;
    std::thread* myThread;

    Command* _c;

    unsigned int timeout;
    void doLoop();
public:
    PollingTimer(Command* c) :  shouldRun(false), _c(c){}
    void start();
    void stop();
};

#endif // POLLINGTIMER_H

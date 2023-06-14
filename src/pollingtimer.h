#ifndef POLLINGTIMER_H
#define POLLINGTIMER_H

#include <QObject>
#include <atomic>
#include <thread>
#include <QThread>

#include "command.h"

class PollingTimer : public QObject
{
    Q_OBJECT
protected:
    std::atomic<bool> shouldRun;
    std::thread* myThread = nullptr;

    Command* _c;

    unsigned int timeout;
    void doLoop();
public:
    QThread workerThread;
    PollingTimer(Command* c) :  shouldRun(false), _c(c){}
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE inline void setDelay(const unsigned int& timeout) {this->timeout = timeout;}
};

#endif // POLLINGTIMER_H

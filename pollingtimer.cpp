#include "pollingtimer.h"
#include <chrono>

void PollingTimer::start(){
    shouldRun = true;
}

void PollingTimer::stop(){
    shouldRun = false;
}

void PollingTimer::doLoop(){
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;

    while(shouldRun){
        begin = std::chrono::steady_clock::now();
        _c->exec();
        end = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(
                    std::chrono::microseconds((this->timeout)
                    - std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()));
    }
}

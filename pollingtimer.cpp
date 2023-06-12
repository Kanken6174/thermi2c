#include "pollingtimer.h"
#include <chrono>

#include "pollingtimer.h"
#include <chrono>

void PollingTimer::doLoop() {
    while (shouldRun) {
        auto start = std::chrono::high_resolution_clock::now();
        _c->exec();
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        if (elapsed < this->timeout) {
            std::this_thread::sleep_for(std::chrono::milliseconds(this->timeout - elapsed));
        }
        fprintf(stderr, "time elapsed: %lld",elapsed);
    }
}

void PollingTimer::start() {
    if (myThread != nullptr) {
        stop();
    }
    shouldRun = true;
    myThread = new std::thread([this]() { this->doLoop(); });
}

void PollingTimer::stop() {
    if (myThread != nullptr) {
        shouldRun = false;
        myThread->join();
        delete myThread;
        myThread = nullptr;
    }
}


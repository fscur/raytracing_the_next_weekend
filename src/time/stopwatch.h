#pragma once
#include <chrono>
#include <functional>
#include <string>

class stopwatch
{
private:
    std::chrono::nanoseconds _initial;
    std::chrono::nanoseconds _stop;
    //std::chrono::nanoseconds _currentNanoSeconds = std::chrono::nanoseconds::zero();
    bool _isRunning = false;

public:
    stopwatch();
    void start();
    void stop();
    void resume();
    double getElapsedSeconds();
    double getElapsedMilliseconds();
    static double measure(const std::function<void(void)> &function);
    static double measure(const std::function<void(void)> &function, const std::string &functionName);
    static double measureAverage(const std::function<void(void)> &function, int numSamples);
    static double measureAverage(const std::function<void(void)> &function, const std::string &functionName, int numSamples);
};
#pragma once

#include <string>
#include "window.h"

class application
{
private:
    static bool _initialized;

public:
    static uint framesPerSecond;
    static double millisecondsPerFrame;

private:
    bool _running;
    window* _window;

private:
    void onInit();
    void onClear();
    void onRender();
    void onInput();
    void onUpdate();
    void onTick();
    void onClose();

public:
    application();
    ~application();

    void run(window* window);
};
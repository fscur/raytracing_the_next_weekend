#pragma once
#include "../common/types.h"

struct mouseEventArgs
{
public:
    void* sender;
    int x;
    int y;
    uint clicks;
    bool leftButtonPressed;
    bool rightButtonPressed;
    bool middleButtonPressed;
    float wheelDelta;
    bool handled;
    bool isCtrlPressed;
    bool isShiftPressed;
    bool isAltPressed;

    mouseEventArgs() :
        sender(nullptr),
        x(0),
        y(0),
        clicks(0),
        leftButtonPressed(false),
        rightButtonPressed(false),
        middleButtonPressed(false),
        wheelDelta(0.0f),
        handled(false),
        isCtrlPressed(false),
        isShiftPressed(false),
        isAltPressed(false)
    {}
};
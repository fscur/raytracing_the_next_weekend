#pragma once
#include "keycode.h"

struct keyboardEventArgs
{
public:
    void* sender;
    keycode key;
    bool isCtrlPressed;
    bool isShiftPressed;
    bool isAltPressed;

    keyboardEventArgs() :
        sender(nullptr),
        key(PHIK_UNKNOWN),
        isCtrlPressed(false),
        isShiftPressed(false),
        isAltPressed(false)
    {}
};
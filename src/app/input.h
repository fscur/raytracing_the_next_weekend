#pragma once

#include "mouseEventHandler.h"
#include "keyboardEventHandler.h"

class input
{
private:
    static void raiseMouseMoveEvent(mouseEventArgs* e);
    static void raiseMouseDownEvent(mouseEventArgs* e);
    static void raiseMouseUpEvent(mouseEventArgs* e);
    static void raiseMouseWheelEvent(mouseEventArgs* e);
    static void raiseKeyDownEvent(keyboardEventArgs* e);
    static void raiseKeyUpEvent(keyboardEventArgs* e);

public:
    static void notifyLeftMouseDown(int x, int y);
    static void notifyRightMouseDown(int x, int y);
    static void notifyMiddleMouseDown(int x, int y);

    static void notifyMouseMove(int x, int y);

    static void notifyLeftMouseUp(int x, int y);
    static void notifyRightMouseUp(int x, int y);
    static void notifyMiddleMouseUp(int x, int y);

    static void notifyMouseWheel(int delta, int x, int y);

    static void notifyKeyDown(int key);
    static void notifyKeyUp(int key);

    static mouseEventHandler* mouseMove;
    static mouseEventHandler* mouseDown;
    static mouseEventHandler* mouseUp;
    static mouseEventHandler* mouseWheel;
    static keyboardEventHandler* keyDown;
    static keyboardEventHandler* keyUp;
};
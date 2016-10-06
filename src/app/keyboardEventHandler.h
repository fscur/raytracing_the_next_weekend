#pragma once
#include "eventHandler.h"
#include "keyboardEventArgs.h"

class keyboardEventHandler :
    public eventHandler<keyboardEventArgs*>
{
};
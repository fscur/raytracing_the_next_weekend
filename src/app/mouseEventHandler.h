#pragma once
#include "eventHandler.h"
#include "mouseEventArgs.h"

class mouseEventHandler :
    public eventHandler<mouseEventArgs*>
{
};
#include <cassert>
#include "../common/types.h"
#include "../time/time.h"
#include "application.h"

bool application::_initialized = false;
uint application::framesPerSecond = 0;
double application::millisecondsPerFrame = 0.0;

application::application() :
    _running(false),
    _window(nullptr)
{
    assert(!_initialized);

    _initialized = true;
    time::start();
}

application::~application()
{
}

void application::run(window* window)
{
    _window = window;

    double timer = 0.0;
    uint frames = 0;
    onInit();

    _running = true;

    while (_running)
    {
        millisecondsPerFrame = time::deltaSeconds * 1000;

        onClear();
        onRender();
        onInput();
        onUpdate();

        time::update();

        if (time::totalSeconds - timer > 1.0)
        {
            timer += 1.0;
            framesPerSecond = frames;
            frames = 0;

            onTick();
        }

        frames++;

        //onSwapbuffers();

        if (_window->closed)
        {
            onClose();
            _running = false;
        }
    }
}

void application::onInit()
{
    _window->init();
}

void application::onClear()
{
    _window->clear();
}

void application::onRender()
{
    _window->render();
}

void application::onInput()
{
    _window->input();
}

void application::onUpdate()
{
    _window->update();
}

void application::onTick()
{
    _window->tick();
}

void application::onClose()
{
    _window->close();
}
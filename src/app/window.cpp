#include "window.h"

window::window(std::wstring title, uint width, uint height) :
    _title(title),
    _width(width),
    _height(height),
    closed(false) {}

window::~window()
{
}

void window::clear()
{
}

void window::render()
{
    onRender();
}

void window::update()
{
    onUpdate();
}

void window::tick()
{
    onTick();
}

void window::onTick() {}
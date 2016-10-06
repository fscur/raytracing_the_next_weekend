#pragma once
#include "../common/types.h"
#include "../io/console.h"
#include "mouseEventArgs.h"
#include "keyboardEventArgs.h"

#ifdef WIN32
#include <Windows.h>
#endif

class window
{
public:
    window(std::wstring title, uint width, uint height);
    virtual ~window();

    void init();
    void clear();
    void render();
    void input();
    void update();
    void tick();
    void close();

    virtual void onInit() = 0;
    virtual void onUpdate() = 0;
    virtual void onRender() = 0;
    virtual void onClosing() = 0;

    virtual void onTick();

private:
    void adjustWindowToScreenBounds();

public:
    bool closed;

protected:
    std::wstring _title;
    uint _width;
    uint _height;

#ifdef WIN32
public:
    HDC getDC() const { return _deviceContext; }
    void setTitle(std::wstring title);

private:
    static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static int convertToKey(WPARAM wParam);

    void createWindow(std::wstring title, uint width, uint height);
    PIXELFORMATDESCRIPTOR getPixelFormatDescriptor();
    void getDpi();

private:
    HWND _windowHandle;
    HINSTANCE _applicationInstance;
    HDC _deviceContext;
    HGLRC _renderingContext;
    DWORD _windowExStyle = 0;
    DWORD _windowStyle = WS_OVERLAPPEDWINDOW;
#endif

};
#include "window.h"
#include "input.h"

#include <windows.h>
#include <windowsx.h>

#undef min
#undef max

#include <algorithm>


int window::convertToKey(WPARAM wParam)
{
    switch (wParam)
    {
    case VK_BACK: return PHIK_BACKSPACE;
    case VK_TAB: return PHIK_TAB;
    case VK_CLEAR: return PHIK_CLEAR;
    case VK_RETURN: return PHIK_RETURN;
    case VK_SHIFT: return PHIK_SHIFT;
    case VK_CONTROL: return PHIK_CTRL;
    case VK_MENU: return PHIK_MENU;
    case VK_PAUSE: return PHIK_PAUSE;
    case VK_CAPITAL: return PHIK_CAPSLOCK;
    case VK_ESCAPE: return PHIK_ESCAPE;
    case VK_SPACE: return PHIK_SPACE;
    case VK_PRIOR: return PHIK_PAGEUP;
    case VK_NEXT: return PHIK_PAGEDOWN;
    case VK_END: return PHIK_END;
    case VK_HOME: return PHIK_HOME;
    case VK_LEFT: return PHIK_LEFT;
    case VK_UP: return PHIK_UP;
    case VK_RIGHT: return PHIK_RIGHT;
    case VK_DOWN: return PHIK_DOWN;
    case VK_SELECT: return PHIK_SELECT;
    case VK_EXECUTE: return PHIK_EXECUTE;
    case VK_SNAPSHOT: return PHIK_PRINTSCREEN;
    case VK_INSERT: return PHIK_INSERT;
    case VK_DELETE: return PHIK_DELETE;
    case VK_HELP: return PHIK_HELP;
    case 0x30: return PHIK_0;
    case 0x31: return PHIK_1;
    case 0x32: return PHIK_2;
    case 0x33: return PHIK_3;
    case 0x34: return PHIK_4;
    case 0x35: return PHIK_5;
    case 0x36: return PHIK_6;
    case 0x37: return PHIK_7;
    case 0x38: return PHIK_8;
    case 0x39: return PHIK_9;
    case 0x41: return PHIK_a;
    case 0x42: return PHIK_b;
    case 0x43: return PHIK_c;
    case 0x44: return PHIK_d;
    case 0x45: return PHIK_e;
    case 0x46: return PHIK_f;
    case 0x47: return PHIK_g;
    case 0x48: return PHIK_h;
    case 0x49: return PHIK_i;
    case 0x4A: return PHIK_j;
    case 0x4B: return PHIK_k;
    case 0x4C: return PHIK_l;
    case 0x4D: return PHIK_m;
    case 0x4E: return PHIK_n;
    case 0x4F: return PHIK_o;
    case 0x50: return PHIK_p;
    case 0x51: return PHIK_q;
    case 0x52: return PHIK_r;
    case 0x53: return PHIK_s;
    case 0x54: return PHIK_t;
    case 0x55: return PHIK_u;
    case 0x56: return PHIK_v;
    case 0x57: return PHIK_w;
    case 0x58: return PHIK_x;
    case 0x59: return PHIK_y;
    case 0x5A: return PHIK_z;
    case VK_APPS: return PHIK_APPLICATION; // TODO: is this the right key?
    case VK_SLEEP: return PHIK_SLEEP;
    case VK_NUMPAD0: return PHIK_KP_0;
    case VK_NUMPAD1: return PHIK_KP_1;
    case VK_NUMPAD2: return PHIK_KP_2;
    case VK_NUMPAD3: return PHIK_KP_3;
    case VK_NUMPAD4: return PHIK_KP_4;
    case VK_NUMPAD5: return PHIK_KP_5;
    case VK_NUMPAD6: return PHIK_KP_6;
    case VK_NUMPAD7: return PHIK_KP_7;
    case VK_NUMPAD8: return PHIK_KP_8;
    case VK_NUMPAD9: return PHIK_KP_9;
    case VK_MULTIPLY: return PHIK_KP_MULTIPLY;
    case VK_ADD: return PHIK_KP_PLUS;
    case VK_SUBTRACT: return PHIK_KP_MINUS;
    case VK_DIVIDE: return PHIK_KP_DIVIDE;
    case VK_DECIMAL: return PHIK_KP_DECIMAL;
    case VK_F1: return PHIK_F1;
    case VK_F2: return PHIK_F2;
    case VK_F3: return PHIK_F3;
    case VK_F4: return PHIK_F4;
    case VK_F5: return PHIK_F5;
    case VK_F6: return PHIK_F6;
    case VK_F7: return PHIK_F7;
    case VK_F8: return PHIK_F8;
    case VK_F9: return PHIK_F9;
    case VK_F10: return PHIK_F10;
    case VK_F11: return PHIK_F11;
    case VK_F12: return PHIK_F12;
    case VK_F13: return PHIK_F13;
    case VK_F14: return PHIK_F14;
    case VK_F15: return PHIK_F15;
    case VK_F16: return PHIK_F16;
    case VK_F17: return PHIK_F17;
    case VK_F18: return PHIK_F18;
    case VK_F19: return PHIK_F19;
    case VK_F20: return PHIK_F20;
    case VK_F21: return PHIK_F21;
    case VK_F22: return PHIK_F22;
    case VK_F23: return PHIK_F23;
    case VK_F24: return PHIK_F24;
    case VK_NUMLOCK: return PHIK_NUMLOCKCLEAR;
    case VK_SCROLL: return PHIK_SCROLLLOCK;
    case VK_BROWSER_BACK: return PHIK_AC_BACK;
    case VK_BROWSER_FORWARD: return PHIK_AC_FORWARD;
    case VK_BROWSER_REFRESH: return PHIK_AC_REFRESH;
    case VK_BROWSER_STOP: return PHIK_AC_STOP;
    case VK_BROWSER_SEARCH: return PHIK_AC_SEARCH;
    case VK_BROWSER_FAVORITES: return PHIK_AC_BOOKMARKS;
    case VK_BROWSER_HOME: return PHIK_AC_HOME;
    case VK_VOLUME_MUTE: return PHIK_MUTE;
    case VK_VOLUME_DOWN: return PHIK_VOLUMEDOWN;
    case VK_VOLUME_UP: return PHIK_VOLUMEUP;
    case VK_MEDIA_NEXT_TRACK: return PHIK_AUDIONEXT;
    case VK_MEDIA_PREV_TRACK: return PHIK_AUDIOPREV;
    case VK_MEDIA_STOP: return PHIK_AUDIOSTOP;
    case VK_MEDIA_PLAY_PAUSE: return PHIK_AUDIOPLAY;
    case VK_LAUNCH_MAIL: return PHIK_MAIL;
    case VK_LAUNCH_MEDIA_SELECT: return PHIK_MEDIASELECT;
    }

    return 0;
}

LRESULT CALLBACK window::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    switch (message)
    {
    case WM_ACTIVATE:
    {
        if (!HIWORD(wParam)) // Is minimized
        {
            // active
        }
        else
        {
            // inactive
        }

        return 0;
    }
    case WM_SYSCOMMAND:
    {
        switch (wParam)
        {
        case SC_SCREENSAVE:
        case SC_MONITORPOWER:
            return 0;
        }
        result = DefWindowProc(hWnd, message, wParam, lParam);
    } break;
    case WM_SETFOCUS:
        //FocusCallback(window, true);
        break;
    case WM_KILLFOCUS:
        //FocusCallback(window, false);
        break;
    case WM_CLOSE:
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        input::notifyKeyDown(convertToKey(wParam));
        break;
    case WM_KEYUP:
    case WM_SYSKEYUP:
        input::notifyKeyUp(convertToKey(wParam));
        break;
    case WM_MOUSEWHEEL:
        auto p = POINT();
        p.x = GET_X_LPARAM(lParam);
        p.y = GET_Y_LPARAM(lParam);
        ScreenToClient(hWnd, &p);
        input::notifyMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam), p.x, p.y);
        break;
    case WM_MOUSEMOVE:
        input::notifyMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_LBUTTONDOWN:
        input::notifyLeftMouseDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_LBUTTONUP:
        input::notifyLeftMouseUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_RBUTTONDOWN:
        input::notifyRightMouseDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_RBUTTONUP:
        input::notifyRightMouseUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_MBUTTONDOWN:
        input::notifyMiddleMouseDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_MBUTTONUP:
        input::notifyMiddleMouseUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        break;
    case WM_SIZE:
        //TODO: Resize
        break;
    default:
        result = DefWindowProc(hWnd, message, wParam, lParam);
    }

    return result;
}

void window::createWindow(std::wstring name, uint width, uint height)
{
    _applicationInstance = GetModuleHandle(NULL);
    WNDCLASSEX wndClass;

    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = (WNDPROC)window::wndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = _applicationInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;

    wndClass.lpszClassName = L"window";
    wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

    if (!RegisterClassEx(&wndClass))
        throw "Could not register window class!";

    auto screenWidth = GetSystemMetrics(SM_CXSCREEN);
    auto screenHeight = GetSystemMetrics(SM_CYSCREEN);

    RECT windowRect;
    windowRect.left = (long)(screenWidth * 0.5f - width * 0.5f);
    windowRect.right = windowRect.left + width;
    windowRect.top = (long)(screenHeight * 0.5f - height * 0.5f);
    windowRect.bottom = windowRect.top + height;

    AdjustWindowRectEx(&windowRect, _windowStyle, FALSE, _windowExStyle);

    _windowHandle = CreateWindowEx(
        0,
        L"window",
        name.c_str(),
        _windowStyle,
        windowRect.left,
        windowRect.top,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        NULL,
        NULL,
        _applicationInstance,
        NULL);

    if (!_windowHandle)
        throw "Could not create the window!";

    _deviceContext = GetDC(_windowHandle);
}

PIXELFORMATDESCRIPTOR window::getPixelFormatDescriptor()
{
    PIXELFORMATDESCRIPTOR result = {};
    result.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    result.nVersion = 1;
    result.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    result.iPixelType = PFD_TYPE_RGBA;
    result.cColorBits = 32;
    result.cDepthBits = 24;
    result.cStencilBits = 8;
    result.cAuxBuffers = 0;
    result.iLayerType = PFD_MAIN_PLANE;
    return result;
}

void window::getDpi()
{
    SetProcessDPIAware(); //true
    HDC screen = GetDC(NULL);
    double hPixelsPerInch = GetDeviceCaps(screen, LOGPIXELSX);
    double vPixelsPerInch = GetDeviceCaps(screen, LOGPIXELSY);
    ReleaseDC(NULL, screen);
}

void window::setTitle(std::wstring title)
{
    SetWindowText(_windowHandle, title.c_str());
}

void window::init()
{
    adjustWindowToScreenBounds();
    createWindow(_title, _width, _height);

    ShowWindow(_windowHandle, SW_SHOW);
    SetForegroundWindow(_windowHandle);
    SetFocus(_windowHandle);

    onInit();
}

void window::adjustWindowToScreenBounds()
{
    auto screenWidth = static_cast<uint>(GetSystemMetrics(SM_CXSCREEN));
    auto screenHeight = static_cast<uint>(GetSystemMetrics(SM_CYSCREEN));

    RECT rectangle = { 0, 0, 0, 0 };
    AdjustWindowRectEx(&rectangle, _windowStyle, FALSE, _windowExStyle);

    auto horizontalBorderSize = static_cast<uint>(rectangle.right - rectangle.left);
    auto verticalBorderSize = static_cast<uint>(rectangle.bottom - rectangle.top);

    _width = std::min(_width, screenWidth);
    _height = std::min(_height, screenHeight - verticalBorderSize);
}

void window::input()
{
    MSG msg;

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        if (msg.message == WM_QUIT)
        {
            closed = true;
            return;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void window::close()
{
    onClosing();

    //releaseGLContext();
    ReleaseDC(_windowHandle, _deviceContext);
    DestroyWindow(_windowHandle);
}
#pragma once
#include "../common/types.h"
#include "../math/rectangle.h"

#ifdef WIN32
#include <Windows.h>
#endif WIN32

class bitmap
{
public:
    bitmap(uint width, uint height);
    bitmap(uint width, uint height, byte* data);
    void setPixel(uint x, uint y, float r, float g, float b);
    void setPixel(uint x, uint y, byte r, byte g, byte b);
    void blit(void* dc);
    void stretchBlit(void* dc, rectangle<int> src, rectangle<int> dest);
    void save(std::string fileName);
    ~bitmap();

private:
#ifdef WIN32
    void createBitmap();
    void createBitmap(byte* data);

#endif

private:
#ifdef WIN32
    HDC _dc;
    HBITMAP _bmp;
    HBITMAP _oldBmp;
    BITMAPINFO _bmi;
#endif

public:
    uint width;
    uint height;

private:
    byte* _data;
};
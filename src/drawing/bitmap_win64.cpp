#include <iostream>
#include "bitmap.h"

bitmap::bitmap(uint width, uint height) :
    width(width),
    height(height)
{
    _data = new byte[width * height * 4];
    createBitmap();
}

bitmap::bitmap(uint width, uint height, byte* data) :
    width(width),
    height(height),
    _data(data)
{
    createBitmap(data);
}

void bitmap::createBitmap(byte* data)
{
    _dc = CreateCompatibleDC(NULL);
    BITMAPINFOHEADER bmih;
    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biWidth = width;
    bmih.biHeight = height;
    bmih.biPlanes = 1;
    bmih.biBitCount = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = 0;
    bmih.biClrUsed = 0;
    bmih.biClrImportant = 0;

    BITMAPINFO dbmi;
    ZeroMemory(&dbmi, sizeof(dbmi));
    dbmi.bmiHeader = bmih;
    dbmi.bmiColors->rgbBlue = 0;
    dbmi.bmiColors->rgbGreen = 0;
    dbmi.bmiColors->rgbRed = 0;
    dbmi.bmiColors->rgbReserved = 0;
    void* bits = (void*)&(data);

    // Create DIB
    _bmp = CreateDIBSection(_dc, &dbmi, DIB_RGB_COLORS, &bits, NULL, 0);
    
    memcpy(bits, &data[0], width * height * 4 * sizeof(byte));

    if ((long)_bmp == ERROR_INVALID_PARAMETER)
    {
        ::MessageBox(NULL, L"Could not load the desired image image", L"Error", MB_OK);
        system("pause");
    }

    if (_bmp == NULL)
    {
        ::MessageBox(NULL, L"Could not load the desired image image", L"Error", MB_OK);
        system("pause");
    }

    _oldBmp = (HBITMAP)SelectObject(_dc, _bmp);
}

void bitmap::createBitmap()
{
    _dc = CreateCompatibleDC(NULL);
    _bmi.bmiHeader.biSize = sizeof(_bmi.bmiHeader);
    _bmi.bmiHeader.biWidth = width;
    _bmi.bmiHeader.biHeight = height;
    _bmi.bmiHeader.biPlanes = 1;
    _bmi.bmiHeader.biBitCount = 32;
    _bmi.bmiHeader.biCompression = BI_RGB;

    _bmp = CreateDIBSection(_dc, &_bmi, DIB_RGB_COLORS, (void**)&_data, NULL, 0);
    if ((long)_bmp == ERROR_INVALID_PARAMETER)
    {
        ::MessageBox(NULL, L"Could not load the desired image image", L"Error", MB_OK);
        system("pause");
    }

    if (_bmp == NULL) 
    {
        ::MessageBox(NULL, L"Could not load the desired image image", L"Error", MB_OK);
        system("pause");
    }

    _oldBmp = (HBITMAP)SelectObject(_dc, _bmp);
}

void bitmap::blit(void* dc)
{
    SetDIBitsToDevice((HDC)_dc, 0, 0, width, height, 0, 0, 0, height, &_data[0], &_bmi, DIB_RGB_COLORS);
    if (!BitBlt((HDC)dc, 0, 0, width, height, (HDC)_dc, 0, 0, SRCCOPY))
    {
        std::cout << "BitBlt Error: " << HRESULT_FROM_WIN32(GetLastError()) << std::endl;
        system("pause");
    }
}

void bitmap::stretchBlit(void * dc, rectangle<int> src, rectangle<int> dest)
{
    SetDIBitsToDevice((HDC)_dc, dest.x, dest.y, dest.w, dest.h, src.x, src.y, 0, height, &_data[0], &_bmi, DIB_RGB_COLORS);
    if (!StretchBlt((HDC)dc, dest.x, dest.y, dest.w, dest.h, (HDC)_dc, src.x, src.y, src.w, src.h, SRCCOPY))
    {
        std::cout << "StretchBlt Error: " << HRESULT_FROM_WIN32(GetLastError()) << std::endl;
        system("pause");
    }
}

void bitmap::save(std::string fileName)
{
    //todo:implement save function
}

void bitmap::setPixel(uint x, uint y, float r, float g, float b)
{
    _data[(y * width * 4) + (x * 4) + 0] = byte(255.9999f * b);
    _data[(y * width * 4) + (x * 4) + 1] = byte(255.9999f * g);
    _data[(y * width * 4) + (x * 4) + 2] = byte(255.9999f * r);
    _data[(y * width * 4) + (x * 4) + 3] = 255;
}

void bitmap::setPixel(uint x, uint y, byte r, byte g, byte b)
{
    _data[(y * width * 4) + (x * 4) + 0] = b;
    _data[(y * width * 4) + (x * 4) + 1] = g;
    _data[(y * width * 4) + (x * 4) + 2] = r;
    _data[(y * width * 4) + (x * 4) + 3] = 255;
}

bitmap::~bitmap()
{
    SelectObject(_dc, _oldBmp);
    DeleteObject(_bmp);
    DeleteDC(_dc);
}
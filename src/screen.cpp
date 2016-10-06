#include <iostream>
#include "screen.h"
#include "io/ppmWriter.h"
#include "io/bitmapWriter.h"
#include "time/stopwatch.h"
#include <future>
#include <queue>

screen::screen(std::wstring name, uint width, uint height) :
    window(name, width, height),
    ASPECT(1.77777778f),
    MIN_SSP(1),
    MAX_SSP(4096),
    MIN_WIDTH(200),
    MAX_WIDTH(800),
    TILE_SIZE(32),
    _processing(false),
    _resultWidth(width),
    _resultHeight(uint(float(MAX_WIDTH) / ASPECT)),
    _currentSsp(MIN_SSP)
{
}

screen::~screen()
{
    delete _scene;
    delete _camera;
    delete _pathTracer;
}

void screen::onInit()
{
    initInput();
    initCamera();
    initScene();
    initPathTracer();
    updateTitle();
    writeInstructionsInConsole();
}

void screen::initInput()
{
    input::keyUp->assign(std::bind(&screen::onKeyUp, this, std::placeholders::_1));
}

void screen::initCamera()
{
    vec3 from(12.0f, 2.0f, 6.0f);
    vec3 at(0.0f, 0.5f, 0.0f);
    float focusDistance = length(from - at);
    float aperture = 0.5f;
    float fov = 20.0f * (glm::pi<float>() / 180.0f);

    _camera = new camera(fov, ASPECT, aperture, focusDistance);
    _camera->lookAt(from, at, vec3(0.0f, 1.0f, 0.0f));
}

void screen::initScene()
{
    _scene = scene::createRandomScene(_camera);
}

void screen::initPathTracer()
{
    _pathTracer = new pathTracer(_scene);
}

void screen::onKeyUp(keyboardEventArgs* args)
{
    if (!_processing)
    {
        switch (args->key)
        {
        case PHIK_RETURN:
            launchPathTracer();
            break;
        case PHIK_UP:
            doubleSsp();
            updateTitle();
            break;
        case PHIK_DOWN:
            halveSsp();
            updateTitle();
            break;
        case PHIK_LEFT:
            halveResolution();
            updateTitle();
            break;
        case PHIK_RIGHT:
            doubleResolution();
            updateTitle();
            break;
        default:
            break;
        }
    }
    else
    {
        switch (args->key)
        {
        case PHIK_ESCAPE:
            _pathTracer->cancel();
            _processing = false;
        default:
            break;
        }
    }
}

void screen::launchPathTracer()
{
    auto task = std::thread([&]
    {
        auto test = "[" +
            std::to_string(_resultWidth) + " x " +
            std::to_string(_resultHeight) + " x " +
            std::to_string(_currentSsp) + " spp]";

        stopwatch::measure([&]
        {
            _processing = true;

            auto horizontalTilesCount = _resultWidth / TILE_SIZE;
            auto verticalTilesCount = _resultHeight / TILE_SIZE;

            auto pixelWriter = new bitmapWriter(_resultWidth, _resultHeight);

            std::queue<std::future<void>> futures;

            auto traceTiles = [&](int i, int j)
            {
                pathTracerRunInfo info;
                info.tile.x = i * TILE_SIZE;
                info.tile.y = j * TILE_SIZE;
                info.tile.w = TILE_SIZE;
                info.tile.h = TILE_SIZE;
                info.width = _resultWidth;
                info.height = _resultHeight;
                info.ssp = _currentSsp;

                _pathTracer->run(info, pixelWriter);
            };

            for (int i = 0; i < horizontalTilesCount; ++i)
                for (int j = 0; j < verticalTilesCount; ++j)
                    futures.push(std::async(std::launch::async, traceTiles, i, j));

            while (futures.size() > 0)
            {
                futures.front().wait();
                futures.pop();
            }

            auto bmp = new bitmap(_resultWidth, _resultHeight, pixelWriter->getData());

            bmp->stretchBlit(
                getDC(),
                rectangle<int>(0, 0, _resultWidth, _resultHeight),
                rectangle<int>(0, 0, _width, _height));

            delete bmp;
            delete pixelWriter;

            _processing = false;
        }, test);
    });

    task.detach();
}

void screen::doubleSsp()
{
    if (_currentSsp == MAX_SSP)
        return;

    _currentSsp *= 2;
}

void screen::halveSsp()
{
    if (_currentSsp == MIN_SSP)
        return;

    _currentSsp /= 2;
}

void screen::doubleResolution()
{
    if (_resultWidth >= MAX_WIDTH)
        return;

    _resultWidth *= 2;
    _resultHeight = uint(float(_resultWidth) / ASPECT);
}

void screen::halveResolution()
{
    if (_resultWidth <= MIN_WIDTH)
        return;

    _resultWidth /= 2;
    _resultHeight = uint(float(_resultWidth) / ASPECT);
}

void screen::updateTitle()
{
    auto title = L"hit enter to start [" +
        std::to_wstring(_resultWidth) + L" x " +
        std::to_wstring(_resultHeight) + L" x " +
        std::to_wstring(_currentSsp) + L" spp]";

    setTitle(title);
}

void screen::writeInstructionsInConsole()
{
    system("cls");
    console::writeLine("Controls");
    console::writeLine("--------");
    console::writeLine("");
    console::writeLine("Up:     double ssp.");
    console::writeLine("Down:   halve ssp.");
    console::writeLine("Left:   double resolution.");
    console::writeLine("Right:  halve resolution.");
    console::writeLine("Enter:  path trace.");
    console::writeLine("ESC:    cancel.");
    console::writeLine("");
}
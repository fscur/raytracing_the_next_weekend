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
    MAX_SSP(32768),
    MIN_WIDTH(200),
    MAX_WIDTH(800),
    TILE_WIDTH(32),
    TILE_HEIGHT(32),
    _processing(false),
    _resultWidth(width),
    _resultHeight(uint(float(MAX_WIDTH) / ASPECT)),
    _currentSsp(MIN_SSP),
    _currentScene(1)
{
}

screen::~screen()
{
    for (auto& scene : _scenes)
        delete scene;

    delete _camera;
    delete _pathTracer;
}

void screen::onInit()
{
    initInput();
    initScene();
    initPathTracer();
    updateTitle();
    writeInstructionsInConsole();
}

void screen::initInput()
{
    input::keyUp->assign(std::bind(&screen::onKeyUp, this, std::placeholders::_1));
}

void screen::initScene()
{
    _scenes.push_back(scene::scene1());
    _scenes.push_back(scene::scene2());
    _scenes.push_back(scene::poolScene());
    _scenes.push_back(scene::earthScene());
    _scenes.push_back(scene::quadLightScene());
    _scenes.push_back(scene::cornelBoxScene());
    _scenes.push_back(scene::cornelBoxSmokeScene());
    _scenes.push_back(scene::finalScene());
}

void screen::initPathTracer()
{
    _pathTracer = new pathTracer(_scenes[0]);
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
        case PHIK_1:
            changeScene(1);
            updateTitle();
            break;
        case PHIK_2:
            changeScene(2);
            updateTitle();
            break;
        case PHIK_3:
            changeScene(3);
            updateTitle();
            break;
        case PHIK_4:
            changeScene(4);
            updateTitle();
            break;
        case PHIK_5:
            changeScene(5);
            updateTitle();
            break;
        case PHIK_6:
            changeScene(6);
            updateTitle();
            break;
        case PHIK_7:
            changeScene(7);
            updateTitle();
            break;
        case PHIK_8:
            changeScene(8);
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
    /*auto test = "[" +
        std::to_string(_resultWidth) + " x " +
        std::to_string(_resultHeight) + " x " +
        std::to_string(_currentSsp) + " spp]";

    stopwatch::measure([&]
    {
        _processing = true;

        auto pixelWriter = new bitmapWriter(_resultWidth, _resultHeight);

        pathTracerRunInfo info;
        info.tile.x = 0;
        info.tile.y = 0;
        info.tile.w = _resultWidth;
        info.tile.h = _resultHeight;
        info.width = _resultWidth;
        info.height = _resultHeight;
        info.ssp = _currentSsp;

        _pathTracer->run(info, pixelWriter);

        auto bmp = new bitmap(_resultWidth, _resultHeight, pixelWriter->getData());

        bmp->stretchBlit(
            getDC(),
            rectangle<int>(0, 0, _resultWidth, _resultHeight),
            rectangle<int>(0, 0, _width, _height));

        delete bmp;
        delete pixelWriter;

        _processing = false;
    }, test);*/

    auto task = std::thread([&]
    {
        auto test = "[" +
            std::to_string(_resultWidth) + " x " +
            std::to_string(_resultHeight) + " x " +
            std::to_string(_currentSsp) + " spp]";

        stopwatch::measure([&]
        {
            _processing = true;

            auto tileWidth = TILE_WIDTH;
            auto tileHeight = TILE_HEIGHT;

            auto horizontalTilesCount = _resultWidth / tileWidth;
            auto verticalTilesCount = _resultHeight / tileHeight;

            auto pixelWriter = new bitmapWriter(_resultWidth, _resultHeight);

            std::queue<std::future<void>> futures;

            auto traceTiles = [&](int i, int j)
            {
                pathTracerRunInfo info;
                info.tile.x = i * tileWidth;
                info.tile.y = j * tileHeight;
                info.tile.w = tileWidth;
                info.tile.h = tileHeight;
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

            std::string fileName = "result.png";
            bmp->save(fileName);
            system(fileName.c_str());

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
    auto title = L"scene: " + std::to_wstring(_currentScene) + L" | "
        L"hit enter to start [" +
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
    console::writeLine("[1..8]: change scene.");
    console::writeLine("ESC:    cancel.");
    console::writeLine("");
}

void screen::changeScene(int sceneId)
{
    _currentScene = sceneId;
    _pathTracer->setScene(_scenes[_currentScene - 1]);
}

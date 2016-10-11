#include "app/application.h"
#include "screen.h"

int main(int argc, char* args[])
{
    application app;

    auto mainScreen = new screen(L"", 800, 450);
    app.run(mainScreen);
    delete mainScreen;

    return 0;
}
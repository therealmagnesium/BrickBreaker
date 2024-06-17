#include "Game.h"
#include <Core/Application.h>

int main(int argc, char* argv[])
{
    AppInfo appInfo;
    appInfo.name = "Brick Breaker";
    appInfo.version = "1.0-dev";
    appInfo.author = "Magnus Ahlstromer V";
    appInfo.screenWidth = 1920;
    appInfo.screenHeight = 1080;

    Game game(appInfo);
    game.Run();

    return 0;
}

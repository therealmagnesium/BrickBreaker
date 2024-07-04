#pragma once
#include "Core/Base.h"
#include "Scene/Brick.h"
#include <raylib.h>
#include <string>

namespace Break::Core
{
    struct MapFileData
    {
        u8 numRows = 0;
        u8 numCols = 0;
        std::string data;
        Vector2 offset{};
        Vector2 spacing{};
        Color brickColors[BRICK_TYPE_COUNT]{};
    };

    class IO
    {
    public:
        static void Init();
        static MapFileData ReadMapFile(const char* path);

    private:
    };
}

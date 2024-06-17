#pragma once
#include "Core/IO.h"
#include "Scene/Brick.h"

#include <vector>
#include <raylib.h>

using namespace Break::Core;

namespace Break::Scene
{
    class Level
    {
    public:
        Level();

        void Load(const char* path);
        void Draw();

    public:
        inline MapFileData& GetData() { return m_mapData; }
        inline Brick* GetBricks() { return m_bricks.data(); }

        inline void SetBrickSpacing(float spacingX, float spacingY) { m_brickSpacing = {spacingX, spacingY}; }
        inline void SetMapOffset(float offsetX, float offsetY) { m_mapOffst = {offsetX, offsetY}; }

    private:
        float m_brickHeight = 50.f; // TODO: Load from file

        Vector2 m_brickSpacing;
        Vector2 m_mapOffst;
        MapFileData m_mapData;
        std::vector<Brick> m_bricks;
    };
}

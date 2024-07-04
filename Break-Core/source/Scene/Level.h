#pragma once
#include "Core/IO.h"
#include "Scene/Brick.h"

#include <vector>
#include <raylib.h>

using namespace Break::Core;

namespace Break::Play
{
    class Level
    {
    public:
        Level();

        void Update();
        void Draw();
        void ActivateBricks();
        void Load(const char* path);

    public:
        inline MapFileData& GetData() { return m_mapData; }
        inline Brick* GetBricks() { return m_bricks.data(); }

        inline void ClearBricks() { m_bricks.clear(); }

    private:
        float m_brickHeight = 50.f; // TODO: Load from file

        MapFileData m_mapData;
        std::vector<Brick> m_bricks;
    };
}

#pragma once
#include "Core/Base.h"
#include "Core/IO.h"
#include "Core/Timer.h"
#include "Scene/Brick.h"
#include "UI/Label.h"

#include <vector>
#include <raylib.h>

using namespace Break::Core;
using namespace Break::UI;

namespace Break::Play
{
    struct LevelIntro
    {
        Timer timer;
        Rectangle rect;
        Label label;
        Color bgColor = WHITE;
    };

    class Level
    {
    public:
        Level();

        void Init(u16 levelIndex);
        void Update();
        void Draw();
        void ActivateBricks();
        void Load(const char* path);

        u16 GetActiveBrickCount();

    public:
        inline u16 GetLevelIndex() { return m_levelIndex; }
        inline LevelIntro& GetIntro() { return m_intro; }
        inline MapFileData& GetData() { return m_mapData; }
        inline Brick* GetBricks() { return m_bricks.data(); }

        inline void ClearBricks() { m_bricks.clear(); }
        inline void SetLevelIndex(u16 index) { m_levelIndex = index; }

    private:
        u16 m_levelIndex = 1;
        float m_brickHeight = 50.f; // TODO: Load from file

        LevelIntro m_intro;
        MapFileData m_mapData;
        std::vector<Brick> m_bricks;
    };
}

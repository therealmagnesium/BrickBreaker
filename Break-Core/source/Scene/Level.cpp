#include "Scene/Level.h"
#include "Scene/Brick.h"
#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/IO.h"

#include <assert.h>
#include <raylib.h>

using namespace Break::Core;

namespace Break::Play
{
    static Application* app = NULL;
    static AppInfo appInfo;

    Level::Level()
    {
        app = Application::Get();
        assert(app);
        appInfo = app->GetInfo();

        m_mapOffst = {0.f, 0.f};
        m_brickSpacing = {50.f, 50.f};
    }

    void Level::Load(const char* path)
    {
        m_mapData = IO::ReadMapFile(path);

        for (u8 i = 0; i < m_mapData.numRows; i++)
        {
            for (u8 j = 0; j < m_mapData.numCols; j++)
            {
                char charID = m_mapData.data[i * m_mapData.numCols + j];
                u8 id = charID - '0'; // Converts char to unsigned integer

                Brick brick;

                float brickWidth = (appInfo.screenWidth / (float)m_mapData.numCols) - m_brickSpacing.x;
                brick.SetSize(brickWidth, m_brickHeight);

                float brickXPos = j * (brick.GetSize().x + m_brickSpacing.x) + m_mapOffst.x;
                float brickYPos = i * (brick.GetSize().y + m_brickSpacing.y) + m_mapOffst.y;
                brick.SetPosition(brickXPos, brickYPos);

                switch (id)
                {
                    case 1:
                    {
                        brick.SetColor(m_mapData.brickColors[0]);
                        brick.SetNumLives(1);
                        break;
                    }
                    case 2:
                    {
                        brick.SetColor(m_mapData.brickColors[1]);
                        brick.SetNumLives(2);
                        break;
                    }
                    case 3:
                    {
                        brick.SetColor(m_mapData.brickColors[2]);
                        brick.SetNumLives(3);
                        break;
                    }

                    default:
                        break;
                }

                m_bricks.push_back(brick);
            }
        }
    }

    void Level::Update()
    {
        for (auto& brick : m_bricks)
            brick.Update();
    }

    void Level::Draw()
    {
        for (auto& brick : m_bricks)
            brick.Draw();
    }
}

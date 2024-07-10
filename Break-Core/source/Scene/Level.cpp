#include "Scene/Level.h"
#include "Core/AssetManager.h"
#include "Scene/Brick.h"
#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/IO.h"
#include "Scene/PowerUp.h"

#include <assert.h>
#include <raylib.h>

using namespace Break::Core;

namespace Break::Play
{
    static Application* app = NULL;

    Level::Level()
    {
        app = Application::Get();
        assert(app);

        this->Init(1);
    }

    void Level::Init(u16 levelIndex)
    {
        AppInfo& appInfo = app->GetInfo();
        Font* labelFont = AssetManager::GetFont("recharge");

        m_levelIndex = levelIndex;

        m_mapData.offset = {0.f, 0.f};
        m_mapData.spacing = {50.f, 50.f};

        m_intro.rect.width = appInfo.screenWidth;
        m_intro.rect.height = 300.f;
        m_intro.rect.x = 0.f;
        m_intro.rect.y = (appInfo.screenHeight / 2.f) - (m_intro.rect.height / 2.f);

        m_intro.timer.isDone = false;
        m_intro.timer.lifetime = 3.f;
        m_intro.bgColor = Fade(BLACK, 0.7f);

        m_intro.label.SetFont(labelFont);
        m_intro.label.SetFontSize(80);
        m_intro.label.SetColor({233, 196, 106, 255});
        m_intro.label.SetText("Level " + std::to_string(m_levelIndex));
        m_intro.label.SetPosition(appInfo.screenWidth / 2.f, appInfo.screenHeight / 2.f);
    }

    void Level::Update()
    {
        m_intro.timer.Update();

        for (u32 i = 0; i < m_bricks.size(); i++)
        {
            if (!m_bricks[i].IsActive())
                m_bricks.erase(m_bricks.begin() + i);

            m_bricks[i].Update();
        }

        for (u32 i = 0; i < m_powerUps.size(); i++)
        {
            if (!m_powerUps[i].active)
                m_powerUps.erase(m_powerUps.begin() + i);

            m_powerUps[i].Update();
        }
    }

    void Level::Draw()
    {
        for (auto& brick : m_bricks)
            brick.Draw();

        for (auto& powerUp : m_powerUps)
            powerUp.Draw();

        if (!m_intro.timer.isDone)
            DrawRectangleRec(m_intro.rect, m_intro.bgColor);
    }

    void Level::ActivateBricks()
    {
        for (Brick& brick : m_bricks)
            brick.SetActive(true);
    }

    void Level::RandomlySpawnPowerUps(float brickX, float brickY)
    {
        u8 spawnCheck = rand() % 4;

        PowerUp powerUp;
        powerUp.radius = 30.f;
        powerUp.speed = 250.f;
        powerUp.position = {brickX, brickY};
        powerUp.type = (PowerUpType)(rand() % POWER_UP_TYPE_COUNT);

        if (spawnCheck == 0)
            m_powerUps.push_back(powerUp);
    }

    void Level::Load(const char* path)
    {
        AppInfo& appInfo = app->GetInfo();
        m_mapData = IO::ReadMapFile(path);

        for (u8 i = 0; i < m_mapData.numRows; i++)
        {
            for (u8 j = 0; j < m_mapData.numCols; j++)
            {
                char charID = m_mapData.data[i * m_mapData.numCols + j];
                u8 id = charID - '0'; // Converts char to unsigned integer

                Brick brick;
                brick.SetLevelHandle(this);

                float brickWidth = (appInfo.screenWidth / (float)m_mapData.numCols) - m_mapData.spacing.x;
                brick.SetSize(brickWidth, m_brickHeight);

                float brickXPos = j * (brick.GetSize().x + m_mapData.spacing.x) + m_mapData.offset.x;
                float brickYPos = i * (brick.GetSize().y + m_mapData.spacing.y) + m_mapData.offset.y;
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

                brick.CreateTintMap();
                m_bricks.push_back(brick);
            }
        }
    }

    u16 Level::GetActiveBrickCount()
    {
        u16 activeBricks = 0;

        for (auto& brick : m_bricks)
        {
            if (brick.IsActive())
                activeBricks++;
        }

        return activeBricks;
    }
}

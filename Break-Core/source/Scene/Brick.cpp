#include "Scene/Brick.h"
#include "Core/Base.h"
#include "Scene/PowerUp.h"
#include "Scene/Level.h"
#include "Core/Application.h"

#include <raylib.h>

using namespace Break::Core;

namespace Break::Play
{
    Brick::Brick()
    {
        m_position = {0.f, 0.f};
        m_size = {80.f, 60.f};
    }

    void Brick::Hit()
    {
        m_hit = true;
        m_hitCount++;
        m_numLives -= 1;
    }

    void Brick::Update()
    {
        m_hit = false;

        if (m_numLives <= 0)
        {
            m_active = false;
            m_levelHandle->RandomlySpawnPowerUps(m_position.x, m_position.y);
        }
    }

    void Brick::Draw()
    {
        if (m_active)
            DrawRectangleV(m_position, m_size, m_hitsToTint[m_hitCount]);

        DrawText(TextFormat("%d", m_numLives), V2_OPEN(m_position), 30, YELLOW);
    }

    void Brick::CreateTintMap()
    {
        m_hitsToTint[0] = m_color;
        m_hitsToTint[1] = ColorTint(m_color, GRAY);
        m_hitsToTint[2] = ColorTint(m_color, DARKGRAY);
    }
}

#include "Scene/Brick.h"
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
            m_active = false;
    }

    void Brick::Draw()
    {
        Color drawColor = m_color;

        if (m_hit)
            drawColor = ColorTint(m_color, GRAY);

        if (m_active)
            DrawRectangleV(m_position, m_size, m_hitsToTint[m_hitCount]);
    }

    void Brick::CreateTintMap()
    {
        m_hitsToTint[0] = m_color;
        m_hitsToTint[1] = ColorTint(m_color, GRAY);
        m_hitsToTint[2] = ColorTint(m_color, DARKGRAY);
    }
}

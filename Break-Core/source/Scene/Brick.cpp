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
            drawColor = ColorTint(m_color, LIGHTGRAY);

        if (m_active)
            DrawRectangleV(m_position, m_size, drawColor);
    }
}

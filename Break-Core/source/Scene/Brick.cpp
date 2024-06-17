#include "Scene/Brick.h"
#include "Core/Application.h"
#include <raylib.h>

using namespace Break::Core;

namespace Break::Scene
{
    Brick::Brick()
    {
        m_position = {0.f, 0.f};
        m_size = {80.f, 60.f};
    }

    void Brick::Update() {}

    void Brick::Draw()
    {
        if (m_active)
            DrawRectangleV(m_position, m_size, m_color);
    }
}

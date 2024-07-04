#include "UI/Slider.h"
#include "Core/Base.h"

#include <raylib.h>
#include <math.h>
#include <string>

namespace Break::UI
{
    Slider::Slider() { m_position = {0.f, 0.f}; }

    void Slider::Update()
    {
        if (m_factor)
        {
            if (*m_factor < 0.f)
                *m_factor = 0.f;

            if (*m_factor > m_capacity)
                *m_factor = m_capacity;
        }
    }

    void Slider::Draw()
    {
        if (m_factor)
        {
            float cappedAmount = fmod(*m_factor, m_capacity);
            if (cappedAmount == 0.f)
                cappedAmount = *m_factor;

            float amountInDegrees = (cappedAmount / m_capacity) * 360.f;
            float endAngle = amountInDegrees + m_startAngle;
            DrawRing(m_position, 30.f, 50.f, m_startAngle, endAngle, 32, m_color);
        }
    }
}

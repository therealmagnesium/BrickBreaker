#pragma once
#include "Core/Base.h"

#include <raylib.h>
#include <string>

namespace Break::UI
{
    /*
     * Note: Sliders have a range from 0 - capacity
     * 0 = Completely empty
     * The default capacity is 100 */

    class Slider
    {
    public:
        Slider();

        void Update();
        void Draw();

    public:
        inline float GetCapacity() { return m_capacity; }
        inline float GetStartAngle() { return m_startAngle; }
        inline float* GetFactor() { return m_factor; }
        inline Color& GetColor() { return m_color; }
        inline Vector2& GetPosition() { return m_position; }

        inline void SetCapacity(float capacity) { m_capacity = capacity; }
        inline void SetStartAngle(float angle) { m_startAngle = angle; }
        inline void SetFactor(float* factor) { m_factor = factor; }
        inline void SetColor(Color color) { m_color = color; }
        inline void SetPosition(float x, float y) { m_position = {x, y}; }

    private:
        float m_capacity = 100.f;
        float m_startAngle = 0.f;
        float* m_factor = NULL;
        Color m_color = BLUE;

        Vector2 m_position;
    };
}

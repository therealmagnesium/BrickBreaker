#pragma once
#include <raylib.h>

#define BRICK_TYPE_COUNT 3

namespace Break::Play
{
    class Brick
    {
    public:
        Brick();

        void Update();
        void Draw();

    public:
        inline bool IsActive() { return m_active; }
        inline Vector2& GetPosition() { return m_position; }
        inline Vector2& GetSize() { return m_size; }
        inline Color& GetColor() { return m_color; }

        inline void SetActive(bool active) { m_active = active; }
        inline void SetPosition(float x, float y) { m_position = {x, y}; }
        inline void SetSize(float width, float height) { m_size = {width, height}; }
        inline void SetColor(Color color) { m_color = color; }

    private:
        bool m_active = true;
        Color m_color = WHITE;

        Vector2 m_position;
        Vector2 m_size;
    };
}

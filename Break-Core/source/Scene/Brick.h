#pragma once
#include <Core/Base.h>
#include <raylib.h>
#include <unordered_map>

#define BRICK_TYPE_COUNT 3

namespace Break::Play
{
    class Brick
    {
    public:
        Brick();

        void Hit();
        void Update();
        void Draw();
        void CreateTintMap();

    public:
        inline bool IsActive() { return m_active; }
        inline u8 GetNumLives() { return m_numLives; }
        inline Vector2& GetPosition() { return m_position; }
        inline Vector2& GetSize() { return m_size; }
        inline Color& GetColor() { return m_color; }

        inline void SetActive(bool active) { m_active = active; }
        inline void SetNumLives(u8 numLives) { m_numLives = numLives; }
        inline void SetPosition(float x, float y) { m_position = {x, y}; }
        inline void SetSize(float width, float height) { m_size = {width, height}; }
        inline void SetColor(Color color) { m_color = color; }

    private:
        bool m_active = true;
        bool m_hit = false;

        u8 m_hitCount = 0;
        s8 m_numLives = 1;

        Color m_color = WHITE;

        Vector2 m_position;
        Vector2 m_size;

        std::unordered_map<u8, Color> m_hitsToTint;
    };
}

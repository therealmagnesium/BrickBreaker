#pragma once
#include <raylib.h>

namespace Break::Scene
{
    class Paddle
    {
    public:
        Paddle();

        void Update();
        void Draw();

    public:
        inline float GetSpeed() { return m_speed; }
        inline float GetVelocity() { return m_velocity; }
        inline Vector2& GetPosition() { return m_position; }
        inline Vector2& GetSize() { return m_size; }

        inline void SetPosition(float x, float y) { m_position = {x, y}; }
        inline void SetSize(float width, float height) { m_size = {width, height}; }
        inline void SetSpeed(float speed) { m_speed = speed; }

    private:
        void HandleCollisions();

    private:
        float m_speed = 200.f;
        float m_velocity = 0.f;

        Vector2 m_position;
        Vector2 m_size;
    };
}

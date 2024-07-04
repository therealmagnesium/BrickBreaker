#pragma once
#include "Core/Base.h"
#include <raylib.h>

namespace Break::Play
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
        inline float GetSprintSpeed() { return m_sprintSpeed; }
        inline float& GetSprintFuel() { return m_sprintFuel; }
        inline Vector2& GetPosition() { return m_position; }
        inline Vector2& GetSize() { return m_size; }
        inline u8 GetNumLives() { return m_numLives; }

        inline void SetNumLives(u8 numLives) { m_numLives = numLives; }
        inline void SetPosition(float x, float y) { m_position = {x, y}; }
        inline void SetSize(float width, float height) { m_size = {width, height}; }
        inline void SetSpeed(float speed) { m_speed = speed; }
        inline void SetSprintSpeed(float speed) { m_sprintSpeed = speed; }
        inline void SetSprintFuel(float fuel) { m_sprintFuel = fuel; }

    private:
        void HandleCollisions();

    private:
        bool m_recovering = false;
        float m_velocity = 0.f;
        float m_speed = 200.f;
        float m_sprintSpeed = 400.f;
        float m_sprintFuel = 100.f;
        u8 m_numLives = 5;

        Vector2 m_position;
        Vector2 m_size;
    };
}

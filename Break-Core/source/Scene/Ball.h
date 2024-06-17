#pragma once
#include "Scene/Brick.h"
#include "Scene/Level.h"
#include "Scene/Paddle.h"
#include <raylib.h>
#include <string>

namespace Break::Play
{
    class Ball
    {
    public:
        Ball();

        void Update();
        void Draw();

    public:
        inline bool IsActive() { return m_active; }
        inline float GetSpeed() { return m_speed; }
        inline float GetRadius() { return m_radius; }
        inline Vector2& GetPosition() { return m_position; }
        inline Vector2& GetVelocity() { return m_velocity; }

        inline void SetActive(bool active) { m_active = active; }
        inline void SetSpeed(float speed) { m_speed = speed; }
        inline void SetRadius(float radius) { m_radius = radius; }
        inline void SetPosition(float x, float y) { m_position = {x, y}; }
        inline void SetPaddleHandle(Paddle* paddle) { m_paddle = paddle; }
        inline void SetLevelHandle(Level* level) { m_level = level; }

    private:
        void HandleInput();
        void HandleMovement();
        void HandleAllCollisions();
        void HandleWallCollisions();
        void HandlePaddleCollisions();
        void HandleBrickCollisions();

    private:
        bool m_active = false;
        float m_speed = 600.f;
        float m_radius = 7.f;

        Vector2 m_position;
        Vector2 m_velocity;

        Level* m_level = NULL;
        Paddle* m_paddle = NULL;
    };
}

#include "Scene/Ball.h"
#include "Core/Application.h"
#include "Core/Base.h"
#include "Scene/Brick.h"

#include <cmath>
#include <raylib.h>
#include <assert.h>

#define MAX_BALL_Y_VEL 1400.f
#define TOP_WALL_FORCE -1.08f;
#define BOUNCE_FORCE -1.005f;

using namespace Break::Core;

namespace Break::Play
{
    static Application* app = NULL;

    Ball::Ball()
    {
        app = Application::Get();
        assert(app);

        m_position = {0.f, 0.f};
        m_velocity = {0.f, 0.f};
    }

    void Ball::Update()
    {
        assert(m_paddle);
        assert(m_level);

        this->HandleInput();
        this->HandleMovement();
        this->HandleAllCollisions();
    }

    void Ball::Draw() { DrawCircleV(m_position, m_radius, {97, 237, 205, 255}); }

    void Ball::HandleInput()
    {
        if (IsKeyPressed(KEY_SPACE) && !m_active)
        {
            m_active = true;
            u8 randDirection = rand() % 2;
            float direction = (randDirection == 0) ? 1.f : -1.f;

            m_velocity = {(m_speed / 1.2f) * direction, -m_speed};
        }
    }

    void Ball::HandleMovement()
    {
        if (!m_active)
        {
            m_position.x = m_paddle->GetPosition().x + m_paddle->GetSize().x / 2.f;
            m_position.y = m_paddle->GetPosition().y - m_paddle->GetSize().y / 2.f - m_radius / 2.f;
        }
        else
        {
            m_position.x += m_velocity.x * GetFrameTime();
            m_position.y += m_velocity.y * GetFrameTime();
        }
    }

    void Ball::HandleAllCollisions()
    {
        this->HandleBrickCollisions();
        this->HandleWallCollisions();
        this->HandlePaddleCollisions();
    }

    void Ball::HandleWallCollisions()
    {
        AppInfo& appInfo = app->GetInfo();

        bool leftWallCheck = m_position.x - m_radius <= 0.f;
        bool rightWallCheck = m_position.x + m_radius >= appInfo.screenWidth;
        bool topWallCheck = m_position.y - m_radius <= 0.f;
        bool bottomWallCheck = m_position.y - m_radius >= appInfo.screenHeight + 200.f;

        if (leftWallCheck || rightWallCheck)
        {
            m_position.x = (m_velocity.x > 0.f) ? appInfo.screenWidth - m_radius : 0.f + m_radius;
            m_velocity.x *= -1.f;
        }

        if (topWallCheck)
        {
            m_velocity.y *= TOP_WALL_FORCE;

            if (m_velocity.y > MAX_BALL_Y_VEL)
                m_velocity.y = MAX_BALL_Y_VEL;
        }

        if (bottomWallCheck)
        {
            m_velocity = {0.f, 0.f};
            m_active = false;
            m_paddle->SetNumLives(m_paddle->GetNumLives() - 1);
            m_level->ClearPowerUps();
        }
    }

    void Ball::HandlePaddleCollisions()
    {
        Rectangle paddleRect;
        paddleRect.x = m_paddle->GetPosition().x;
        paddleRect.y = m_paddle->GetPosition().y;
        paddleRect.width = m_paddle->GetSize().x;
        paddleRect.height = m_paddle->GetSize().y;
        if (CheckCollisionCircleRec(m_position, m_radius, paddleRect))
        {
            if (m_velocity.y > 0.f)
            {
                float switchDirection = (m_paddle->GetVelocity() > 0.f) ? 1.f : -1.f;
                float centerOfPaddle = m_paddle->GetPosition().x + m_paddle->GetSize().x / 2.f;
                float distanceToPaddle = m_position.x - centerOfPaddle;

                m_velocity.y *= -1.f;
                m_velocity.x = distanceToPaddle / (m_paddle->GetSize().x / 2.f) * m_speed;
            }
        }
    }

    void Ball::HandleBrickCollisions()
    {
        for (u8 i = 0; i < m_level->GetActiveBrickCount(); i++)
        {
            Brick& brick = m_level->GetBricks()[i];
            if (brick.IsActive())
            {
                float ballLeft = m_position.x - m_radius;
                float ballRight = m_position.x + m_radius;
                float ballTop = m_position.y - m_radius;
                float ballBottom = m_position.y + m_radius;

                float brickLeft = brick.GetPosition().x;
                float brickRight = brick.GetPosition().x + brick.GetSize().x;
                float brickTop = brick.GetPosition().y;
                float brickBottom = brick.GetPosition().y + brick.GetSize().y;

                float ballToBrickX = m_position.x - (brick.GetPosition().x + brick.GetSize().x / 2.f);
                float ballToBrickY = m_position.y - (brick.GetPosition().y + brick.GetSize().y / 2.f);
                bool horizontalCheck = fabs(ballToBrickX) < (brick.GetSize().x / 2.f + m_radius * 2.f / 3.f);
                bool verticalCheck = fabs(ballToBrickY) < (brick.GetSize().y / 2.f + m_radius * 2.f / 3.f);

                // Hit from below
                if ((ballTop <= brickBottom) && (ballTop > brickBottom - brick.GetSize().y / 2.f) && horizontalCheck &&
                    (m_velocity.y < 0.f))
                {
                    brick.Hit();
                    m_velocity.y *= -1.f;
                }
                // Hit from above
                else if ((ballBottom >= brickTop) && (ballBottom < brickTop + brick.GetSize().y / 2.f) &&
                         horizontalCheck && (m_velocity.y > 0.f))
                {
                    brick.Hit();
                    m_velocity.y *= -1.f;
                }
                // Hit from left
                else if ((ballRight >= brickLeft) && (ballRight < brickLeft + brick.GetSize().x / 2.f) &&
                         verticalCheck && (m_velocity.x > 0.f))
                {
                    brick.Hit();
                    m_velocity.x *= -1.f;
                }
                // Hit from right
                else if ((ballLeft <= brickRight) && (ballLeft > brickRight - brick.GetSize().x / 2.f) &&
                         verticalCheck && (m_velocity.x < 0.f))
                {
                    brick.Hit();
                    m_velocity.x *= -1.f;
                }
            }
        }
    }
}

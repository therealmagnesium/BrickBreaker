#include "Scene/Paddle.h"
#include "Core/Application.h"
#include "Core/Base.h"

#include <raylib.h>
#include <assert.h>

#define SPRINT_FUEL_DEC_SPEED 80.f
#define SPRINT_FUEL_INC_SPEED 35.f
#define SPRINT_FUEL_REC_SPEED 15.f

using namespace Break::Core;

namespace Break::Play
{
    static Application* app = NULL;
    static AppInfo appInfo;

    Paddle::Paddle()
    {
        app = Application::Get();
        assert(app);

        appInfo = app->GetInfo();

        m_position = {0.f, 0.f};
        m_size = {80.f, 50.f};
    }

    void Paddle::Update()
    {
        static float maxSprintFuel = m_sprintFuel;
        s8 horizontalInput = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);

        if (m_sprintFuel <= 0.f)
            m_recovering = true;

        if (m_recovering && m_sprintFuel > 50.f)
            m_recovering = false;

        if (IsKeyDown(KEY_LEFT_SHIFT) && !m_recovering)
        {
            m_velocity = horizontalInput * m_sprintSpeed;
            m_sprintFuel -= GetFrameTime() * SPRINT_FUEL_DEC_SPEED;
        }
        else if (m_recovering)
        {
            m_velocity = horizontalInput * m_speed;
            m_sprintFuel += GetFrameTime() * SPRINT_FUEL_REC_SPEED;
        }
        else
        {
            m_velocity = horizontalInput * m_speed;
            m_sprintFuel += GetFrameTime() * SPRINT_FUEL_INC_SPEED;
        }

        m_position.x += m_velocity * GetFrameTime();

        this->HandleCollisions();
    }

    void Paddle::Draw() { DrawRectangleV(m_position, m_size, WHITE); }

    void Paddle::HandleCollisions()
    {
        if (m_position.x <= 0.f)
            m_position.x = 0.f;

        if (m_position.x + m_size.x >= appInfo.screenWidth)
            m_position.x = appInfo.screenWidth - m_size.x;
    }
}

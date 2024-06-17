#include "Scene/Paddle.h"
#include "Core/Application.h"
#include "Core/Base.h"

#include <raylib.h>
#include <assert.h>

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
        s8 horizontalInput = IsKeyDown(KEY_RIGHT) - IsKeyDown(KEY_LEFT);
        m_velocity = horizontalInput * m_speed;
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

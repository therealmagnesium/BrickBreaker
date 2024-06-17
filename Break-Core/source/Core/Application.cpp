#include "Core/Application.h"
#include "Core/Base.h"

#include <raylib.h>
#include <math.h>

namespace Break::Core
{

    static Vector2 originalScreenDimensions;
    Application* Application::s_instance = NULL;

    Application::Application(const AppInfo& info) : m_info(info)
    {
        s_instance = this;
        originalScreenDimensions = {(float)info.screenWidth, (float)info.screenHeight};

        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_FULLSCREEN_MODE);
        InitWindow(m_info.screenWidth, m_info.screenHeight, m_info.name.c_str());
        SetTargetFPS(60);
    }

    void Application::Run()
    {
        if (!m_primaryCamera)
        {
            TraceLog(LOG_FATAL, "Cannot run application because no primary camera set!");
            this->Quit();
            return;
        }

        while (m_running)
        {
            this->HandleEvents();
            this->OnUpdate();

            BeginDrawing();
            {
                ClearBackground(m_clearColor);

                BeginMode2D(*m_primaryCamera);
                {
                    this->OnRender();
                }
                EndMode2D();

                this->OnUIRender();
            }
            EndDrawing();
        }

        CloseWindow();
    }

    void Application::Quit() { m_running = false; }

    void Application::HandleEvents()
    {
        m_running = !WindowShouldClose();

        if (IsWindowResized())
        {
            m_info.screenWidth = GetScreenWidth();
            m_info.screenHeight = GetScreenHeight();

            float widthRatio = m_info.screenWidth / originalScreenDimensions.x;
            m_primaryCamera->zoom = widthRatio;

            TraceLog(LOG_INFO, "Window resized to %dx%d", m_info.screenWidth, m_info.screenHeight);
        }
    }
}

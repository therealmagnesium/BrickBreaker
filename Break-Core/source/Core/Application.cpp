#include "Core/Application.h"
#include "Core/Base.h"
#include "Scene/Scene.h"

#include <raylib.h>
#include <math.h>

using namespace Break::Play;

namespace Break::Core
{
    static Vector2 originalScreenDimensions;
    static Scene* currentScene = NULL;

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
        if (!currentScene)
        {

            TraceLog(LOG_FATAL, "Cannot run application because no scene set!");
            this->Quit();
            return;
        }

        if (!currentScene->GetPrimaryCamera())
        {
            TraceLog(LOG_FATAL, "Cannot run application because no primary camera set!");
            this->Quit();
            return;
        }

        while (m_running)
        {
            this->HandleEvents();
            currentScene->OnUpdate();

            if (currentScene)
            {
                BeginDrawing();
                {
                    ClearBackground(currentScene->GetClearColor());

                    BeginMode2D(*currentScene->GetPrimaryCamera());
                    {
                        currentScene->OnRender();
                    }
                    EndMode2D();

                    currentScene->OnUIRender();
                }
                EndDrawing();
            }
        }

        CloseWindow();
    }

    void Application::Quit()
    {
        m_running = false;

        Scene* temp = currentScene;
        currentScene = NULL;
        delete temp;
    }

    void Application::SetScenes(Scene** scenes, u8 numScenes)
    {
        m_scenes.resize(numScenes);

        for (u8 i = 0; i < numScenes; i++)
            m_scenes[i] = scenes[i];
    }

    void Application::SwitchToScene(u8 sceneIndex)
    {
        if (sceneIndex > m_scenes.size())
        {
            TraceLog(LOG_ERROR, "Failed to switch to scene %d because outside of index", sceneIndex);
            return;
        }

        Scene* prevScene = currentScene;
        currentScene = m_scenes[sceneIndex];

        if (prevScene)
            delete prevScene;
    }

    void Application::HandleEvents()
    {
        m_running = !WindowShouldClose();

        if (IsWindowResized())
        {
            m_info.screenWidth = GetScreenWidth();
            m_info.screenHeight = GetScreenHeight();

            Camera2D* camera = currentScene->GetPrimaryCamera();
            float widthRatio = m_info.screenWidth / originalScreenDimensions.x;
            camera->zoom = widthRatio;

            TraceLog(LOG_INFO, "Window resized to %dx%d", m_info.screenWidth, m_info.screenHeight);
        }
    }
}

#include "Core/Application.h"
#include "Core/AssetManager.h"
#include "Core/Base.h"
#include "Core/IO.h"

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

        ConfigFlags flags = (ConfigFlags)(FLAG_WINDOW_RESIZABLE | FLAG_FULLSCREEN_MODE | FLAG_VSYNC_HINT);
        SetConfigFlags(flags);
        InitWindow(m_info.screenWidth, m_info.screenHeight, m_info.name.c_str());
        SetExitKey(KEY_NULL);
        // SetTargetFPS(60);

        IO::Init();
    }

    Application::~Application()
    {
        for (u8 i = 0; i < m_scenes.size(); i++)
        {
            if (m_scenes[i])
            {
                TraceLog(LOG_INFO, "Deleting scene, %s", m_scenes[i]->GetDebugName().c_str());
                delete m_scenes[i];
                m_scenes[i] = NULL;
            }
        }

        m_scenes.clear();
        CloseWindow();

        TraceLog(LOG_INFO, "%s has finished running!", m_info.name.c_str());
    }

    void Application::Run()
    {
        if (!currentScene)
        {
            TraceLog(LOG_FATAL, "Cannot run application because no scene set!");
            this->Quit();
            return;
        }

        if (!currentScene->GetPrimaryCamera() && !currentScene->CanLoadAssets())
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
    }

    void Application::Quit()
    {
        m_running = false;
        AssetManager::Clean();
    }

    void Application::SetScenes(Scene** scenes, u8 numScenes)
    {
        m_scenes.resize(numScenes);

        for (u8 i = 0; i < numScenes; i++)
        {
            m_scenes[i] = scenes[i];
            m_scenes[i]->SetSceneIndex(i);
        }
    }

    void Application::ToggleFullscreen()
    {
        if (!IsWindowFullscreen())
        {
            s32 monitor = GetCurrentMonitor();
            SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
            ::ToggleFullscreen();
        }
        else
        {
            ::ToggleFullscreen();
            SetWindowSize(m_info.screenWidth, m_info.screenHeight);
        }
    }

    void Application::SwitchToScene(u8 sceneIndex)
    {
        for (Scene* scene : m_scenes)
        {
            if (scene->CanLoadAssets())
                m_loadingScene = scene;
        }

        if (sceneIndex == m_loadingScene->GetSceneIndex())
        {
            TraceLog(LOG_ERROR, "Switching to loading scene is done automatically!", sceneIndex);
            return;
        }

        if (sceneIndex > m_scenes.size())
        {
            TraceLog(LOG_ERROR, "Failed to switch to scene %d because outside of index!", sceneIndex);
            return;
        }

        if (!m_scenes[sceneIndex])
        {
            TraceLog(LOG_ERROR, "Failed to switch to scene %d because it's null!", sceneIndex);
            return;
        }

        AssetManager::Clean();

        s8 prevSceneIndex = m_sceneIndex;
        m_sceneIndex = sceneIndex;
        m_loadingScene->OnCreate();

        currentScene = m_scenes[sceneIndex];
        currentScene->OnCreate();
        /*
                if (prevSceneIndex != -1 && m_scenes[prevSceneIndex] && !m_scenes[prevSceneIndex]->CanLoadAssets())
                {
                    delete m_scenes[prevSceneIndex];
                    m_scenes[prevSceneIndex] = NULL;
                }*/
    }

    void Application::HandleEvents()
    {
        m_running = !WindowShouldClose();

        if (IsWindowResized())
        {
            Camera2D* camera = currentScene->GetPrimaryCamera();
            float widthRatio = GetScreenWidth() / (float)m_info.screenWidth;
            camera->zoom = widthRatio;

            TraceLog(LOG_INFO, "Window resized to %dx%d", GetScreenWidth(), GetScreenHeight());
        }
    }
}

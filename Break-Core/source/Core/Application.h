#pragma once
#include "Core/Base.h"
#include "Scene/Scene.h"

#include <raylib.h>
#include <string>
#include <vector>

using namespace Break::Play;

namespace Break::Core
{
    struct AppInfo
    {
        std::string name;
        std::string version;
        std::string author;
        u16 screenWidth;
        u16 screenHeight;
        bool vsync = false;
    };

    class Application
    {
    public:
        Application(const AppInfo& info);
        ~Application();

        void Run();
        void Quit();
        void SwitchToScene(u8 sceneIndex);

    public:
        static inline Application* Get() { return s_instance; }
        inline bool IsRunning() { return m_running; }
        inline s8 GetSceneIndex() { return m_sceneIndex; }
        inline AppInfo& GetInfo() { return m_info; }

    protected:
        void SetScenes(Scene** scenes, u8 numScenes);

    private:
        void HandleEvents();

    private:
        bool m_running = true;
        AppInfo m_info;
        s8 m_sceneIndex = -1;

        Scene* m_loadingScene;
        std::vector<Scene*> m_scenes;

    private:
        static Application* s_instance;
    };
}

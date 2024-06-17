#pragma once
#include "Core/Base.h"

#include <raylib.h>
#include <string>

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

        void Run();
        void Quit();

    public:
        static inline Application* Get() { return s_instance; }
        inline bool IsRunning() { return m_running; }
        inline AppInfo& GetInfo() { return m_info; }

        inline void SetClearColor(Color color) { m_clearColor = color; }
        inline void SetPrimaryCamera(Camera2D* camera) { m_primaryCamera = camera; }

    protected:
        virtual void OnUpdate() {}
        virtual void OnRender() {}
        virtual void OnUIRender() {}

    private:
        void HandleEvents();

    private:
        bool m_running = true;

        AppInfo m_info;
        Color m_clearColor = RAYWHITE;
        Camera2D* m_primaryCamera = NULL;

    private:
        static Application* s_instance;
    };
}

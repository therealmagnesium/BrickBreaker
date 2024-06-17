#pragma once
#include <raylib.h>
#include <string>

namespace Break::Play
{
    class Scene
    {
    public:
        Scene();

        virtual void OnUpdate() {}
        virtual void OnRender() {}
        virtual void OnUIRender() {}

    public:
        inline Color GetClearColor() { return m_clearColor; }
        inline Camera2D* GetPrimaryCamera() { return m_primaryCamera; }

        inline void SetClearColor(Color color) { m_clearColor = color; }
        inline void SetPrimaryCamera(Camera2D* camera) { m_primaryCamera = camera; }

    private:
        Color m_clearColor = RAYWHITE;
        Camera2D* m_primaryCamera = NULL;
    };
}

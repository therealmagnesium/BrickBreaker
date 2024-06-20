#pragma once
#include "Core/Base.h"

#include <raylib.h>
#include <string>

namespace Break::Play
{
    class Scene
    {
    public:
        Scene();

        virtual void OnCreate() {}
        virtual void OnUpdate() {}
        virtual void OnRender() {}
        virtual void OnUIRender() {}

    public:
        inline bool CanLoadAssets() { return m_canLoadAssets; }
        inline s8 GetSceneIndex() { return m_sceneIndex; }
        inline std::string& GetDebugName() { return m_debugName; }
        inline Color GetClearColor() { return m_clearColor; }
        inline Camera2D* GetPrimaryCamera() { return m_primaryCamera; }

        inline void EnableAssetLoading() { m_canLoadAssets = true; }
        inline void SetSceneIndex(s8 sceneIndex) { m_sceneIndex = sceneIndex; }
        inline void SetDebugName(const std::string& name) { m_debugName = name; }
        inline void SetClearColor(Color color) { m_clearColor = color; }
        inline void SetPrimaryCamera(Camera2D* camera) { m_primaryCamera = camera; }

    private:
        s8 m_sceneIndex = -1;
        bool m_canLoadAssets = false;
        std::string m_debugName = "default";
        Color m_clearColor = RAYWHITE;
        Camera2D* m_primaryCamera = NULL;
    };
}

#pragma once
#include <Core/Application.h>
#include <Core/Base.h>
#include <Scene/Scene.h>

#include <raylib.h>

using namespace Break::Core;
using namespace Break::Play;

class TitleScene : public Scene
{
public:
    TitleScene();

    void OnUpdate() override;
    void OnUIRender() override;

private:
    Camera2D m_camera;
};

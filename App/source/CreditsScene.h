#pragma once

#include <Core/Application.h>
#include <Core/Base.h>
#include <Scene/Button.h>
#include <Scene/Label.h>
#include <Scene/Scene.h>

#include <raylib.h>

using namespace Break::Core;
using namespace Break::Play;

enum CreditSceneLabels
{
    CREDITS_LABEL_TITLE = 0,
    CREDITS_LABEL_COUNT,
};

class CreditsScene : public Scene
{
public:
    CreditsScene();

    void OnCreate() override;
    void OnUpdate() override;
    void OnRender() override;
    void OnUIRender() override;

private:
    Camera2D m_camera;
    Label m_labels[CREDITS_LABEL_COUNT];
};

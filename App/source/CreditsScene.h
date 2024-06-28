#pragma once

#include <Core/Application.h>
#include <Core/Base.h>

#include <Scene/Background.h>
#include <Scene/Button.h>
#include <Scene/Button.h>
#include <Scene/Label.h>
#include <Scene/Scene.h>

#include <raylib.h>

using namespace Break::Core;
using namespace Break::Play;

enum CreditSceneLabel
{
    CREDITS_LABEL_TITLE = 0,
    CREDITS_LABEL_MAGNUS,
    CREDITS_LABEL_LOGAN,
    CREDITS_LABEL_MONIKA,
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
    void CreateBackground();
    void CreateLabels();

private:
    Camera2D m_camera;
    Background m_background;
    Label m_labels[CREDITS_LABEL_COUNT];
    CreditSceneLabel m_creditLabelIndex = CREDITS_LABEL_MAGNUS;
};

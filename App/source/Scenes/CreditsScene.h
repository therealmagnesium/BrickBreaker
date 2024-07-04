#pragma once

#include <Core/Application.h>
#include <Core/Base.h>

#include <Scene/Background.h>
#include <Scene/Scene.h>

#include <UI/CanvasContext.h>

#include <raylib.h>

using namespace Break::Core;
using namespace Break::Play;
using namespace Break::UI;

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
    void CreateCanvas();

private:
    Camera2D m_camera;
    Background m_background;
    CanvasContext m_canvas;
    u8 m_creditLabelIndex = CREDITS_LABEL_MAGNUS;
};

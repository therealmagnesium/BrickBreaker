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

enum TitleSceneLabels
{
    TITLE_LABEL_TITLE = 0,
    TITLE_LABEL_COUNT,
};

enum TitleSceneButtons
{
    TITLE_BUTTON_PLAY = 0,
    TITLE_BUTTON_OPTIONS,
    TITLE_BUTTON_CREDITS,
    TITLE_BUTTON_QUIT,
    TITLE_BUTTON_COUNT,
};

class TitleScene : public Scene
{
public:
    TitleScene();

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
};

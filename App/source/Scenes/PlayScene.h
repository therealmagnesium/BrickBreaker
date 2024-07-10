#pragma once
#include <Core/Application.h>
#include <Core/Timer.h>

#include <Scene/Background.h>
#include <Scene/Ball.h>
#include <Scene/Brick.h>
#include <Scene/Level.h>
#include <Scene/Paddle.h>
#include <Scene/Scene.h>

#include <UI/CanvasContext.h>

#include <raylib.h>

using namespace Break::Core;
using namespace Break::Play;
using namespace Break::UI;

enum PlaySceneLabels
{
    PLAY_LABEL_STAMINA = 0,
    PLAY_LABEL_LIVES,
    PLAY_LABEL_LEVEL,
    PLAY_LABEL_BRICKS,
    PLAY_LABEL_COUNT,
};

enum PlaySceneSliders
{
    PLAY_SLIDER_STAMINA = 0,
    PLAY_SLIDER_COUNT,
};

class PlayScene : public Scene
{
public:
    PlayScene();

    void OnCreate() override;
    void OnUpdate() override;
    void OnRender() override;
    void OnUIRender() override;

private:
    void Reset();
    void CreateBackground();
    void CreateBall();
    void CreatePaddle();
    void CreateLevel();
    void CreateCanvas();
    void CreateOverlay();

private:
    u16 m_currentLevel = 4;

    Camera2D m_camera;
    CanvasContext m_canvas;

    Background m_background;
    Rectangle m_overlayRect;

    Ball m_ball;
    Level m_level;
    Paddle m_paddle;
};

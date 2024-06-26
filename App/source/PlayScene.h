#pragma once
#include <Core/Application.h>

#include <Scene/Background.h>
#include <Scene/Ball.h>
#include <Scene/Brick.h>
#include <Scene/Level.h>
#include <Scene/Paddle.h>
#include <Scene/Scene.h>

#include <raylib.h>

using namespace Break::Core;
using namespace Break::Play;

class PlayScene : public Scene
{
public:
    PlayScene();

    void OnCreate() override;
    void OnUpdate() override;
    void OnRender() override;
    void OnUIRender() override;

private:
    void CreateBackground();
    void CreateBall();
    void CreatePaddle();
    void CreateLevel();

private:
    Background m_background;
    Ball m_ball;
    Level m_level;
    Paddle m_paddle;
    Camera2D m_camera;
};

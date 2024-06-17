#pragma once
#include <Core/Application.h>

#include <Scene/Ball.h>
#include <Scene/Brick.h>
#include <Scene/Level.h>
#include <Scene/Paddle.h>

#include <raylib.h>

using namespace Break::Core;
using namespace Break::Scene;

class Game : public Application
{
public:
    Game(const AppInfo& info);

    void OnUpdate() override;
    void OnRender() override;
    void OnUIRender() override;

private:
    void CreateBall();
    void CreatePaddle();
    void CreateLevel();

private:
    Ball m_ball;
    Level m_level;
    Paddle m_paddle;
    Camera2D m_camera;
};

#include "Game.h"

#include <Core/Application.h>
#include <Core/IO.h>
#include <raylib.h>

Game::Game(const AppInfo& info) : Application(info)
{
    m_camera.target = {0.f, 0.f};
    m_camera.offset = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    this->CreateLevel();
    this->CreatePaddle();
    this->CreateBall();

    this->SetClearColor({20, 20, 20, 255});
    this->SetPrimaryCamera(&m_camera);

    DisableCursor();
}

void Game::OnUpdate()
{
    if (IsKeyPressed(KEY_ESCAPE))
        this->Quit();

    m_paddle.Update();
    m_ball.Update();
}

void Game::OnRender()
{
    m_paddle.Draw();
    m_ball.Draw();
    m_level.Draw();
}

void Game::OnUIRender()
{
    AppInfo& appInfo = this->GetInfo();
    DrawFPS(20, appInfo.screenHeight - 20);
}

void Game::CreateBall()
{
    float ballX = m_paddle.GetPosition().x + m_paddle.GetSize().x / 2.f;
    float ballY = m_paddle.GetPosition().y - m_paddle.GetSize().y / 2.f;

    m_ball.SetPosition(ballX, ballY);
    m_ball.SetRadius(15.f);
    m_ball.SetSpeed(800.f);
    m_ball.SetPaddleHandle(&m_paddle);
    m_ball.SetLevelHandle(&m_level);
}

void Game::CreatePaddle()
{
    AppInfo& info = this->GetInfo();

    m_paddle.SetSpeed(800.f);
    m_paddle.SetSize(250.f, 30.f);

    float spawnX = info.screenWidth / 2.f - m_paddle.GetSize().x / 2.f;
    float spawnY = info.screenHeight - 100.f;
    m_paddle.SetPosition(spawnX, spawnY);
}

void Game::CreateLevel()
{
    m_level.SetMapOffset(20.f, 80.f);
    m_level.SetBrickSpacing(30.f, 20.f);
    m_level.Load("assets/levels/level1.map");
}
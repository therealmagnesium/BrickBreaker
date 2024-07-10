#include "PlayScene.h"
#include "../Game.h"

#include <Core/Application.h>
#include <Core/AssetManager.h>
#include <Core/IO.h>
#include <Core/Timer.h>

#include <raylib.h>
#include <assert.h>

static Application* app = NULL;

PlayScene::PlayScene()
{
    app = Application::Get();
    assert(app);

    this->SetDebugName("Play");
}

void PlayScene::OnCreate()
{
    m_camera.target = {0.f, 0.f};
    m_camera.offset = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    this->Reset();

    this->SetClearColor({20, 20, 20, 255});
    this->SetPrimaryCamera(&m_camera);
}

void PlayScene::OnUpdate()
{
    if (IsKeyPressed(KEY_ESCAPE))
        app->SwitchToScene(TITLE_SCENE);

    m_background.Update();
    m_level.Update();
    m_paddle.Update();
    m_ball.Update();
    m_canvas.UpdateUIElements();

    if (!m_ball.IsActive())
        m_paddle.SetSprintFuel(100.f);

    m_canvas.labels[PLAY_LABEL_LIVES].SetText(TextFormat("Lives: %d", m_paddle.GetNumLives()));
    m_canvas.labels[PLAY_LABEL_BRICKS].SetText(TextFormat("Bricks: %d", m_level.GetActiveBrickCount()));

    if (m_level.GetActiveBrickCount() == 0)
    {
        m_currentLevel++;
        this->Reset();
    }

    if (m_paddle.GetNumLives() == 0)
        app->SwitchToScene(TITLE_SCENE);

    if (m_paddle.IsRecovering())
        m_canvas.sliders[PLAY_SLIDER_STAMINA].SetColor(RED);
    else if (m_paddle.GetSprintFuel() == 100.f)
        m_canvas.sliders[PLAY_SLIDER_STAMINA].SetColor(GREEN);
    else
        m_canvas.sliders[PLAY_SLIDER_STAMINA].SetColor(SKYBLUE);

    if (m_level.GetIntro().timer.isDone)
        m_canvas.labels[PLAY_LABEL_LEVEL].SetActive(false);
}

void PlayScene::OnRender()
{
    m_background.Draw();
    m_paddle.Draw();
    m_ball.Draw();
    m_level.Draw();

    DrawRectangleRec(m_overlayRect, Fade({28, 12, 59, 255}, 0.6f));
}

void PlayScene::OnUIRender()
{
    AppInfo& appInfo = app->GetInfo();
    DrawFPS(20, appInfo.screenHeight - 20);
    m_canvas.DrawUIElements();
}

void PlayScene::CreateBackground()
{
    Shader* shader = AssetManager::GetShader("stars");
    m_background.SetShader(shader);
    m_background.SetColorFactor(0.5f, 0.2f, 0.5f);
}

void PlayScene::CreateBall()
{
    float ballX = m_paddle.GetPosition().x + m_paddle.GetSize().x / 2.f;
    float ballY = m_paddle.GetPosition().y - m_paddle.GetSize().y / 2.f;

    m_ball.SetActive(false);
    m_ball.SetPosition(ballX, ballY);
    m_ball.SetRadius(18.f);
    m_ball.SetSpeed(800.f);
    m_ball.SetPaddleHandle(&m_paddle);
    m_ball.SetLevelHandle(&m_level);
}

void PlayScene::CreatePaddle()
{
    AppInfo& info = app->GetInfo();

    m_paddle.SetSpeed(800.f);
    m_paddle.SetSprintSpeed(1400.f);
    m_paddle.SetSize(200.f, 30.f);
    m_paddle.SetNumLives(5);

    float spawnX = info.screenWidth / 2.f - m_paddle.GetSize().x / 2.f;
    float spawnY = info.screenHeight - 100.f;
    m_paddle.SetPosition(spawnX, spawnY);
}

void PlayScene::CreateLevel()
{
    std::string levelPath = "assets/levels/level" + std::to_string(m_currentLevel) + ".map";

    m_level.Init(m_currentLevel);
    m_level.ClearBricks();
    m_level.ClearPowerUps();
    m_level.Load(levelPath.c_str());
    m_level.ActivateBricks();
}

void PlayScene::CreateCanvas()
{
    AppInfo& appInfo = app->GetInfo();
    Font* labelFont = AssetManager::GetFont("recharge");

    m_canvas.SetLabelCount(PLAY_LABEL_COUNT);
    m_canvas.SetSliderCount(PLAY_SLIDER_COUNT);

    m_canvas.sliders[PLAY_SLIDER_STAMINA].SetStartAngle(-90.f);
    m_canvas.sliders[PLAY_SLIDER_STAMINA].SetCapacity(100.f);
    m_canvas.sliders[PLAY_SLIDER_STAMINA].SetFactor(&m_paddle.GetSprintFuel());
    m_canvas.sliders[PLAY_SLIDER_STAMINA].SetColor(SKYBLUE);
    m_canvas.sliders[PLAY_SLIDER_STAMINA].SetPosition(450.f, 75.f);

    for (u8 i = 0; i < PLAY_LABEL_COUNT; i++)
    {
        m_canvas.labels[i].SetColor({233, 196, 106, 255});
        m_canvas.labels[i].SetFont(labelFont);
        m_canvas.labels[i].SetFontSize(70);
    }

    m_canvas.labels[PLAY_LABEL_STAMINA].SetText("Stamina");
    m_canvas.labels[PLAY_LABEL_STAMINA].SetPosition(m_canvas.sliders[PLAY_SLIDER_STAMINA].GetPosition().x - 250.f,
                                                    m_canvas.sliders[PLAY_SLIDER_STAMINA].GetPosition().y);

    m_canvas.labels[PLAY_LABEL_LIVES].SetPosition(appInfo.screenWidth - 300.f,
                                                  m_canvas.sliders[PLAY_SLIDER_STAMINA].GetPosition().y);

    m_canvas.labels[PLAY_LABEL_LEVEL] = m_level.GetIntro().label;

    m_canvas.labels[PLAY_LABEL_BRICKS].SetPosition(appInfo.screenWidth / 2.f,
                                                   m_canvas.labels[PLAY_LABEL_LIVES].GetPosition().y);
}

void PlayScene::CreateOverlay()
{
    AppInfo& appInfo = app->GetInfo();

    m_overlayRect.x = 0.f;
    m_overlayRect.y = 0.f;
    m_overlayRect.width = appInfo.screenWidth;
    m_overlayRect.height = 150.f;
}

void PlayScene::Reset()
{
    this->CreateBackground();
    this->CreateLevel();
    this->CreatePaddle();
    this->CreateBall();
    this->CreateCanvas();
    this->CreateOverlay();

    if (m_level.GetActiveBrickCount() == 0)
        app->SwitchToScene(CREDITS_SCENE);
}

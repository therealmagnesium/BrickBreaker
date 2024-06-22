#include "TitleScene.h"
#include "Game.h"

#include <Core/Application.h>
#include <Core/AssetManager.h>
#include <Core/Base.h>
#include <raylib.h>
#include <assert.h>

using namespace Break::Core;
using namespace Break::Play;

static Application* app = NULL;

TitleScene::TitleScene()
{
    app = Application::Get();
    assert(app);

    this->SetDebugName("Title");
}

void TitleScene::OnCreate()
{
    AppInfo& appInfo = app->GetInfo();

    m_camera.target = {0.f, 0.f};
    m_camera.offset = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    this->CreateTitleLabel();
    this->CreateButtons();

    this->SetClearColor({20, 20, 20, 255});
    this->SetPrimaryCamera(&m_camera);
}

void TitleScene::OnUpdate()
{
    if (m_buttons[TITLE_BUTTON_PLAY].IsClicked())
        app->SwitchToScene(PLAY_SCENE);

    if (m_buttons[TITLE_BUTTON_CREDITS].IsClicked())
        app->SwitchToScene(CREDITS_SCENE);

    if (m_buttons[TITLE_BUTTON_QUIT].IsClicked())
        app->Quit();

    this->UpdateButtons();
}

void TitleScene::OnRender()
{
    for (u8 i = 0; i < TITLE_BUTTON_COUNT; i++)
        m_buttons[i].Draw();

    m_titleLabel.Draw();
}

void TitleScene::OnUIRender()
{
    /*
    AppInfo& appInfo = app->GetInfo();
    DrawFPS(20, appInfo.screenHeight - 20);*/
}

void TitleScene::CreateButtons()
{
    AppInfo& appInfo = app->GetInfo();
    Texture2D* basicButtonTexture = AssetManager::GetTexture("basic button");
    Texture2D* quitButtonTexture = AssetManager::GetTexture("quit button");

    for (u8 i = 0; i < TITLE_BUTTON_COUNT; i++)
    {
        if (i == TITLE_BUTTON_QUIT)
            continue;

        m_buttons[i].SetScale(2.5f, 2.3f);
        m_buttons[i].SetPosition(appInfo.screenWidth / 2.f, appInfo.screenHeight / 2.f + (i * 200.f));
        m_buttons[i].SetTexture(basicButtonTexture);
        m_buttons[i].SetHoverColor({222, 222, 222, 255});

        Label& label = m_buttons[i].GetLabel();
        label.SetColor({233, 196, 106, 255});

        switch (i)
        {
            case TITLE_BUTTON_PLAY:
            {
                label.SetText("Play!");
                break;
            }
            case TITLE_BUTTON_OPTIONS:
            {
                label.SetText("Options");
                break;
            }
            case TITLE_BUTTON_CREDITS:
            {
                label.SetText("Credits");
                break;
            }
        }

        m_buttons[TITLE_BUTTON_QUIT].SetScale(3.f, 3.f);
        m_buttons[TITLE_BUTTON_QUIT].SetPosition(200.f, appInfo.screenHeight - 200.f);
        m_buttons[TITLE_BUTTON_QUIT].SetTexture(quitButtonTexture);
        m_buttons[TITLE_BUTTON_QUIT].SetHoverColor({180, 180, 180, 255});
    }
}

void TitleScene::CreateTitleLabel()
{
    AppInfo& appInfo = app->GetInfo();
    Font* labelFont = AssetManager::GetFont("recharge");

    m_titleLabel.SetFontSize(120);
    m_titleLabel.SetFont(labelFont);
    m_titleLabel.SetFontFilter(TEXTURE_FILTER_POINT);
    m_titleLabel.SetText("Brick Breaker");
    m_titleLabel.SetColor({233, 196, 106, 255});
    m_titleLabel.SetSpacing(4.f);
    m_titleLabel.SetPosition(appInfo.screenWidth / 2.f, 250.f);
}

void TitleScene::UpdateButtons()
{
    for (u8 i = 0; i < TITLE_BUTTON_COUNT; i++)
        m_buttons[i].Update();
}

#include "CreditsScene.h"
#include "Game.h"

#include <Core/Application.h>
#include <Core/AssetManager.h>
#include <Core/Base.h>
#include <Scene/Button.h>
#include <Scene/Label.h>
#include <Scene/Scene.h>

#include <assert.h>
#include <raylib.h>

using namespace Break::Core;
using namespace Break::Play;

static Application* app = NULL;

CreditsScene::CreditsScene()
{
    app = Application::Get();
    assert(app);

    this->SetDebugName("Credits");
}

void CreditsScene::OnCreate()
{
    m_camera.target = {0.f, 0.f};
    m_camera.offset = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    AppInfo& appInfo = app->GetInfo();
    Font* labelFont = AssetManager::GetFont("recharge");

    m_labels[CREDITS_LABEL_TITLE].SetFontSize(100);
    m_labels[CREDITS_LABEL_TITLE].SetFont(labelFont);
    m_labels[CREDITS_LABEL_TITLE].SetFontFilter(TEXTURE_FILTER_POINT);
    m_labels[CREDITS_LABEL_TITLE].SetText("Credits");
    m_labels[CREDITS_LABEL_TITLE].SetColor({233, 196, 106, 255});
    m_labels[CREDITS_LABEL_TITLE].SetSpacing(4.f);
    m_labels[CREDITS_LABEL_TITLE].SetPosition(appInfo.screenWidth / 2.f, 100.f);

    this->SetClearColor({20, 20, 20, 255});
    this->SetPrimaryCamera(&m_camera);
}

void CreditsScene::OnUpdate()
{
    if (IsKeyPressed(KEY_ESCAPE))
        app->SwitchToScene(TITLE_SCENE);
}

void CreditsScene::OnRender()
{
    for (u8 i = 0; i < CREDITS_LABEL_COUNT; i++)
        m_labels[i].Draw();
}

void CreditsScene::OnUIRender() {}

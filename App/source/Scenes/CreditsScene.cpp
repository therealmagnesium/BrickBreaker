#include "CreditsScene.h"
#include "../Game.h"

#include <Core/Application.h>
#include <Core/AssetManager.h>
#include <Core/Base.h>

#include <Scene/Scene.h>

#include <UI/Button.h>
#include <UI/Label.h>

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

    this->CreateBackground();
    this->CreateCanvas();

    this->SetClearColor({20, 20, 20, 255});
    this->SetPrimaryCamera(&m_camera);
}

void CreditsScene::OnUpdate()
{
    m_canvas.labels[m_creditLabelIndex].SetActive(true);

    if (IsKeyPressed(KEY_ESCAPE))
        app->SwitchToScene(TITLE_SCENE);

    if (IsKeyPressed(KEY_LEFT))
        m_creditLabelIndex--;

    if (IsKeyPressed(KEY_RIGHT))
        m_creditLabelIndex++;

    if (m_creditLabelIndex < CREDITS_LABEL_MAGNUS)
        m_creditLabelIndex = CREDITS_LABEL_MAGNUS;
    else if (m_creditLabelIndex > CREDITS_LABEL_MONIKA)
        m_creditLabelIndex = CREDITS_LABEL_MONIKA;

    m_background.Update();
    m_canvas.UpdateUIElements();
}

void CreditsScene::OnRender() { m_background.Draw(); }

void CreditsScene::OnUIRender()
{
    m_canvas.labels[CREDITS_LABEL_TITLE].Draw();
    m_canvas.labels[m_creditLabelIndex].Draw();
}

void CreditsScene::CreateBackground()
{
    Shader* shader = AssetManager::GetShader("stars");
    m_background.SetShader(shader);
    m_background.SetColorFactor(0.4f, 0.3f, 0.3f);
}

void CreditsScene::CreateCanvas()
{
    AppInfo& appInfo = app->GetInfo();
    Font* labelFont = AssetManager::GetFont("recharge");

    m_canvas.SetLabelCount(CREDITS_LABEL_COUNT);

    m_canvas.labels[CREDITS_LABEL_TITLE].SetSpacing(4.f);
    m_canvas.labels[CREDITS_LABEL_TITLE].SetFont(labelFont);
    m_canvas.labels[CREDITS_LABEL_TITLE].SetFontFilter(TEXTURE_FILTER_POINT);
    m_canvas.labels[CREDITS_LABEL_TITLE].SetText("Credits");
    m_canvas.labels[CREDITS_LABEL_TITLE].SetFontSize(100);
    m_canvas.labels[CREDITS_LABEL_TITLE].SetColor({233, 196, 106, 255});
    m_canvas.labels[CREDITS_LABEL_TITLE].SetPosition(appInfo.screenWidth / 2.f, 100.f);

    for (u8 i = 0; i < CREDITS_LABEL_COUNT; i++)
    {
        if (i == CREDITS_LABEL_TITLE)
            continue;

        m_canvas.labels[i].SetActive(false);
        m_canvas.labels[i].SetFontSize(80);
        m_canvas.labels[i].SetSpacing(4.f);
        m_canvas.labels[i].SetFont(labelFont);
        m_canvas.labels[i].SetFontFilter(TEXTURE_FILTER_POINT);

        float labelX = appInfo.screenWidth / 2.f;
        float labelY = appInfo.screenHeight / 2.f + 400.f;
        m_canvas.labels[i].SetPosition(labelX, labelY);

        switch (i)
        {
            case CREDITS_LABEL_MAGNUS:
            {
                m_canvas.labels[i].SetText("Magnus Ahlstromer V");
                break;
            }
            case CREDITS_LABEL_LOGAN:
            {
                m_canvas.labels[i].SetText("Logan Jones");
                break;
            }
            case CREDITS_LABEL_MONIKA:
            {
                m_canvas.labels[i].SetText("Monika Pelto");
                break;
            }
        }
    }
}

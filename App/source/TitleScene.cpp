#include "TitleScene.h"
#include "Game.h"

#include <Core/Application.h>
#include <raylib.h>
#include <assert.h>

using namespace Break::Core;
using namespace Break::Play;

static Application* app = NULL;

TitleScene::TitleScene()
{
    app = Application::Get();
    assert(app);

    m_camera.target = {0.f, 0.f};
    m_camera.offset = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    this->SetClearColor({20, 20, 20, 255});
    this->SetPrimaryCamera(&m_camera);
}

void TitleScene::OnUpdate()
{
    if (IsKeyPressed(KEY_ESCAPE))
        app->Quit();

    if (IsKeyPressed(KEY_SPACE))
        app->SwitchToScene(PLAY_SCENE);
}

void TitleScene::OnUIRender()
{
    AppInfo& appInfo = app->GetInfo();

    DrawText("Press space to play!", 400, 300, 40, RAYWHITE);
    DrawFPS(20, appInfo.screenHeight - 20);
}

#include "LoadingScene.h"
#include "Game.h"

#include <Core/Application.h>
#include <Core/AssetManager.h>
#include <Core/Base.h>
#include <assert.h>

#include <raylib.h>

using namespace Break::Core;

static Application* app = NULL;

LoadingScene::LoadingScene()
{
    app = Application::Get();
    assert(app);

    this->SetDebugName("Loading");
    this->EnableAssetLoading(); // Must be done in constructor
}

void LoadingScene::OnCreate()
{
    switch (app->GetSceneIndex())
    {
        // Load assets for the title scene
        case TITLE_SCENE:
        {
            AssetManager::AddTexture("button", "assets/textures/button.png");
            AssetManager::AddFont("recharge", "assets/fonts/recharge.ttf");
            break;
        }
        // Load assets for the play scene
        case PLAY_SCENE:
        {
            break;
        }

        default:
            break;
    }

    m_loading = false;
}

void LoadingScene::OnUpdate() {}

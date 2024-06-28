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
            AssetManager::AddTexture("basic button", "assets/textures/button.png");
            AssetManager::AddTexture("quit button", "assets/textures/quit_button.png");
            AssetManager::AddFont("recharge", "assets/fonts/recharge.ttf", 120);
            AssetManager::AddShader("panning squares", {"", "assets/shaders/PanningSquares_fs.glsl"});
            break;
        }
        // Load assets for the play scene
        case PLAY_SCENE:
        {
            AssetManager::AddShader("panning squares", {"", "assets/shaders/PanningSquares_fs.glsl"});
            AssetManager::AddShader("test", {"assets/shaders/TestShader_vs.glsl", "assets/shaders/TestShader_fs.glsl"});
            break;
        }

        case CREDITS_SCENE:
        {
            AssetManager::AddFont("recharge", "assets/fonts/recharge.ttf", 100);
            AssetManager::AddShader("test", {"assets/shaders/TestShader_vs.glsl", "assets/shaders/TestShader_fs.glsl"});
            break;
        }

        default:
            break;
    }

    m_loading = false;
}

void LoadingScene::OnUpdate() {}

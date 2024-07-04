#include "Game.h"
#include "Scenes/CreditsScene.h"
#include "Scenes/LoadingScene.h"
#include "Scenes/PlayScene.h"
#include "Scenes/TitleScene.h"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Scene/Scene.h>

#include <raylib.h>

using namespace Break::Core;
using namespace Break::Play;

Game::Game(const AppInfo& info) : Application(info)
{
    m_playScene = new PlayScene();
    m_titleScene = new TitleScene();
    m_loadingScene = new LoadingScene();
    m_creditsScene = new CreditsScene();

    m_scenes[TITLE_SCENE] = m_titleScene;
    m_scenes[PLAY_SCENE] = m_playScene;
    m_scenes[CREDITS_SCENE] = m_creditsScene;
    m_scenes[LOADING_SCENE] = m_loadingScene;

    // this->ToggleFullscreen();
    this->SetScenes(m_scenes, 4);
    this->SwitchToScene(TITLE_SCENE);
}

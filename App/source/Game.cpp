#include "Game.h"
#include "PlayScene.h"
#include "TitleScene.h"

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

    m_scenes[PLAY_SCENE] = m_playScene;
    m_scenes[TITLE_SCENE] = m_titleScene;

    this->SetScenes(m_scenes, 2);
    this->SwitchToScene(TITLE_SCENE);
}

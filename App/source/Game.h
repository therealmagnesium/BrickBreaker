#pragma once
#include "PlayScene.h"
#include "TitleScene.h"
#include "LoadingScene.h"
#include "CreditsScene.h"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Scene/Scene.h>

enum GameScenes
{
    TITLE_SCENE = 0,
    PLAY_SCENE,
    CREDITS_SCENE,
    LOADING_SCENE,
    GAME_SCENE_COUNT,
};

using namespace Break::Core;
using namespace Break::Play;

/*
 * Note: All client scenes added to the core
 *      application's collection of scenes
 *      are already taken care of, freeing
 *      memory wise.*/

class Game : public Application
{
public:
    Game(const AppInfo& info);

private:
    PlayScene* m_playScene;
    TitleScene* m_titleScene;
    LoadingScene* m_loadingScene;
    CreditsScene* m_creditsScene;

    Scene* m_scenes[GAME_SCENE_COUNT]{};
};

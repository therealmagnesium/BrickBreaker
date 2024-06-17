#pragma once
#include "PlayScene.h"
#include "TitleScene.h"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Scene/Scene.h>

#define PLAY_SCENE 0
#define TITLE_SCENE 1
#define SCENE_COUNT 2

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
    Scene* m_scenes[SCENE_COUNT]{};
};

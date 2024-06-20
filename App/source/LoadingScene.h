#pragma once
#include <Core/Application.h>
#include <Core/Base.h>

using namespace Break::Core;

class LoadingScene : public Scene
{
public:
    LoadingScene();

    void OnCreate() override;
    void OnUpdate() override;

private:
    bool m_loading = true;
};

#include "Scene/Background.h"
#include "Core/Application.h"
#include "Core/Base.h"

#include <raylib.h>
#include <assert.h>

using namespace Break::Core;
using namespace Break::Play;

static Application* app = NULL;

namespace Break::Play
{
    Background::Background()
    {
        app = Application::Get();
        assert(app);
        const AppInfo& appInfo = app->GetInfo();

        Image blankImage = GenImageColor(appInfo.screenWidth, appInfo.screenHeight, BLANK);
        m_texture = LoadTextureFromImage(blankImage);
        UnloadImage(blankImage);
    }

    Background::~Background() { UnloadTexture(m_texture); }

    void Background::Update()
    {
        const AppInfo& appInfo = app->GetInfo();

        if (m_shader)
        {
            float time = GetTime();
            Vector2 resolution = {(float)appInfo.screenWidth, (float)appInfo.screenHeight};

            s32 timeLocation = GetShaderLocation(*m_shader, "uTime");
            s32 resolutionLocation = GetShaderLocation(*m_shader, "uResolution");
            s32 colorFactorLocation = GetShaderLocation(*m_shader, "uColorFactor");

            SetShaderValue(*m_shader, timeLocation, &time, SHADER_UNIFORM_FLOAT);
            SetShaderValue(*m_shader, resolutionLocation, &resolution, SHADER_UNIFORM_VEC2);
            SetShaderValue(*m_shader, colorFactorLocation, &m_colorFactor, SHADER_UNIFORM_VEC3);
        }
    }

    void Background::Draw()
    {
        if (m_shader)
        {
            BeginShaderMode(*m_shader);
            DrawTexture(m_texture, 0, 0, WHITE);
            EndShaderMode();
        }
    }
}

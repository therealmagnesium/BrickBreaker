#include "Scene/PowerUp.h"
#include "Core/Base.h"
#include "Core/Application.h"

#include <assert.h>
#include <raylib.h>

using namespace Break::Core;

static Application* app = NULL;

namespace Break::Play
{
    PowerUp::PowerUp()
    {
        app = Application::Get();
        assert(app);
    }

    void PowerUp::Update()
    {
        const AppInfo& appInfo = app->GetInfo();

        if (position.y - radius > appInfo.screenHeight)
            active = false;

        switch (type)
        {
            case POWER_UP_SPEED:
            {
                color = {194, 174, 85, 255};
                break;
            }

            case POWER_UP_MULTIBALL:
            {
                color = {92, 194, 85, 255};
                break;
            }
            default:
                break;
        }

        position.y += speed * GetFrameTime();
    }

    void PowerUp::Draw()
    {
        if (active)
            DrawCircleV(position, radius, color);
    }
}

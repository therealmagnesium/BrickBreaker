#pragma once
#include "Core/Base.h"
#include <raylib.h>

namespace Break::Play
{
    enum PowerUpType
    {
        POWER_UP_SPEED,
        POWER_UP_MULTIBALL,
        POWER_UP_TYPE_COUNT
    };

    struct PowerUp
    {
        bool active = true;
        float radius = 40.f;
        float speed = 300.f;
        PowerUpType type = POWER_UP_SPEED;
        Vector2 position = {0.f, 0.f};
        Color color = WHITE;

        PowerUp();
        void Update();
        void Draw();
    };
}

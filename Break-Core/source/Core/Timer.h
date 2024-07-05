#pragma once
#include "Core/Base.h"

namespace Break::Core
{
    struct Timer
    {
        bool isDone = false;
        float lifetime = 0.f;

        void Start();
        void Update();
    };
}

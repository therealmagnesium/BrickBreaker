#include "Core/Timer.h"
#include <raylib.h>

namespace Break::Core
{
    void Timer::Start() { isDone = false; }

    void Timer::Update()
    {
        static float startTime = lifetime;

        if (lifetime <= 0.f)
        {
            isDone = true;
            lifetime = startTime;
        }

        if (!isDone)
            lifetime -= GetFrameTime();
    }
}

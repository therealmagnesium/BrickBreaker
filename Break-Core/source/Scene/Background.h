#pragma once
#include "Core/Base.h"

#include <raylib.h>
#include <string>

namespace Break::Play
{
    class Background
    {
    public:
        Background();
        ~Background();

        void Update();
        void Draw();

    public:
        inline void SetShader(Shader* shader) { m_shader = shader; }

    private:
        Shader* m_shader = NULL;
        Texture2D m_texture;
    };
}

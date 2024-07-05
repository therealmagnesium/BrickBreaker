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
        inline void SetColorFactor(float x, float y, float z) { m_colorFactor = {x, y, z}; }

    private:
        Shader* m_shader = NULL;
        Texture2D m_texture;
        Vector3 m_colorFactor;
    };
}

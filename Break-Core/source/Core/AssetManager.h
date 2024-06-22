#pragma once
#include "Core/Base.h"

#include <raylib.h>
#include <unordered_map>
#include <string>

namespace Break::Core
{
    struct ShaderSource
    {
        std::string vertexPath;
        std::string fragmentPath;
    };

    class AssetManager
    {
    public:
        static void AddTexture(const std::string& name, const std::string& path);
        static void AddFont(const std::string& name, const std::string& path, u32 fontSize = 80.f);
        static void AddShader(const std::string& name, const ShaderSource& source);
        static void Clean();

    public:
        static inline Texture* GetTexture(const std::string& name) { return m_textures[name]; }
        static inline Font* GetFont(const std::string& name) { return m_fonts[name]; }
        static inline Shader* GetShader(const std::string& name) { return m_shaders[name]; }

    private:
        static std::unordered_map<std::string, Texture*> m_textures;
        static std::unordered_map<std::string, Font*> m_fonts;
        static std::unordered_map<std::string, Shader*> m_shaders;
    };
}

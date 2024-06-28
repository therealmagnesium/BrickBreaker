#include "Core/AssetManager.h"

#include <raylib.h>
#include <unordered_map>
#include <string>

namespace Break::Core
{
    std::unordered_map<std::string, Texture2D*> AssetManager::m_textures{};
    std::unordered_map<std::string, Font*> AssetManager::m_fonts{};
    std::unordered_map<std::string, Shader*> AssetManager::m_shaders{};

    void AssetManager::AddTexture(const std::string& name, const std::string& path)
    {
        if (m_textures.find(name) != m_textures.end())
        {
            TraceLog(LOG_ERROR, "Failed to add %s to texture assets because it is already added!", name.c_str());
            return;
        }

        Texture2D texture = LoadTexture(path.c_str());
        Texture2D* textureHandle = new Texture2D();
        *textureHandle = texture;

        if (!textureHandle)
        {
            TraceLog(LOG_ERROR, "Failed to load %s into texture assets!", path.c_str());
            return;
        }

        m_textures[name] = textureHandle;
    }

    void AssetManager::AddFont(const std::string& name, const std::string& path, u32 fontSize)
    {
        if (m_fonts.find(name) != m_fonts.end())
        {
            TraceLog(LOG_ERROR, "Failed to add %s to font assets because it is already added!", name.c_str());
            return;
        }

        Font font = LoadFontEx(path.c_str(), fontSize, NULL, 0);
        Font* fontHandle = new Font();
        *fontHandle = font;

        if (!fontHandle)
        {
            TraceLog(LOG_ERROR, "Failed to load %s into font assets!", name.c_str());
            return;
        }

        m_fonts[name] = fontHandle;
    }

    void AssetManager::AddShader(const std::string& name, const ShaderSource& source)
    {
        if (m_shaders.find(name) != m_shaders.end())
        {
            TraceLog(LOG_ERROR, "Failed to add %s to shader assets because it is already added!", name.c_str());
            return;
        }

        const char* vertexPath = 0;
        const char* fragmentPath = 0;

        if (!source.vertexPath.empty())
            vertexPath = source.vertexPath.c_str();

        if (!source.fragmentPath.empty())
            fragmentPath = source.fragmentPath.c_str();

        Shader shader = LoadShader(vertexPath, fragmentPath);
        Shader* shaderHandle = new Shader();
        *shaderHandle = shader;

        if (!shaderHandle)
        {
            TraceLog(LOG_ERROR, "Failed to load %s into shader assets!", name.c_str());
            return;
        }

        m_shaders[name] = shaderHandle;
    }

    void AssetManager::Clean()
    {
        for (auto& [name, texture] : m_textures)
        {
            if (texture)
            {
                TraceLog(LOG_INFO, "Deleting %s from texture assets", name.c_str());
                UnloadTexture(*texture);
                delete texture;
            }
        }

        for (auto& [name, font] : m_fonts)
        {
            if (font)
            {
                TraceLog(LOG_INFO, "Deleting %s from font assets", name.c_str());
                UnloadFont(*font);
                delete font;
            }
        }

        for (auto& [name, shader] : m_shaders)
        {
            if (shader)
            {
                TraceLog(LOG_INFO, "Deleting %s from shader assets", name.c_str());
                UnloadShader(*shader);
                delete shader;
            }
        }

        m_textures.clear();
        m_fonts.clear();
        m_shaders.clear();

        TraceLog(LOG_INFO, "Successfully cleaned all assets!");
    }
}

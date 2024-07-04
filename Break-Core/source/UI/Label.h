#pragma once
#include "Core/Base.h"

#include <raylib.h>
#include <string>

namespace Break::UI
{
    class Label
    {
    public:
        Label();

        void Draw();
        void SetFontFilter(TextureFilter filter);

    public:
        inline bool IsActive() { return m_active; }
        inline float GetSpacing() { return m_spacing; }
        inline float GetRotation() { return m_rotation; }
        inline u16 GetFontSize() { return m_fontSize; }
        inline Color GetColor() { return m_color; }
        inline std::string& GetText() { return m_text; }
        inline Vector2& GetPosition() { return m_position; }

        inline void SetActive(bool active) { m_active = active; }
        inline void SetSpacing(float spacing) { m_spacing = spacing; }
        inline void SetRotation(float rotation) { m_rotation = rotation; }
        inline void SetFontSize(u16 size) { m_fontSize = size; }
        inline void SetColor(Color color) { m_color = color; }
        inline void SetText(const std::string& text) { m_text = text; }
        inline void SetPosition(float x, float y) { m_position = {x, y}; }
        inline void SetFont(Font* font) { m_font = font; }

    private:
        bool m_active = true;
        float m_spacing = 4.f;
        float m_rotation = 0.f;
        u16 m_fontSize = 32;
        Color m_color = WHITE;
        Font* m_font = NULL;

        std::string m_text;
        Vector2 m_position;
    };
}

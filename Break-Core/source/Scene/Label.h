#pragma once
#include "Core/Base.h"
#include <raylib.h>
#include <string>

namespace Break::Play
{
    class Label
    {
    public:
        Label();

        void Draw();
        void SetFontFilter(TextureFilter filter);

    public:
        inline bool IsActive() { return m_active; }
        inline u16 GetFontSize() { return m_fontSize; }
        inline float GetSpacing() { return m_spacing; }
        inline Color GetColor() { return m_color; }
        inline std::string& GetText() { return m_text; }
        inline Vector2& GetPosition() { return m_position; }

        inline void SetActive(bool active) { m_active = active; }
        inline void SetFontSize(u16 size) { m_fontSize = size; }
        inline void SetSpacing(float spacing) { m_spacing = spacing; }
        inline void SetColor(Color color) { m_color = color; }
        inline void SetText(const std::string& text) { m_text = text; }
        inline void SetPosition(float x, float y) { m_position = {x, y}; }
        inline void SetFont(Font* font) { m_font = font; }

    private:
        bool m_active = true;
        u16 m_fontSize = 32;
        float m_spacing = 4.f;
        Color m_color = WHITE;
        Font* m_font = NULL;

        std::string m_text;
        Vector2 m_position;
    };
}

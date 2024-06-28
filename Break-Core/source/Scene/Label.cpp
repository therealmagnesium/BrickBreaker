#include "Scene/Label.h"
#include <raylib.h>

namespace Break::Play
{
    Label::Label()
    {
        m_position = {0.f, 0.f};
        m_spacing = 4.f;
        m_text = "default";
        m_fontSize = 50;
    }

    void Label::Draw()
    {
        Font drawFont = GetFontDefault();

        if (m_font)
            drawFont = *m_font;

        Vector2 origin;
        Vector2 labelSize = MeasureTextEx(drawFont, m_text.c_str(), m_fontSize, m_spacing);

        origin.x = labelSize.x / 2.f;
        origin.y = labelSize.y / 2.f;

        if (!m_text.empty() && m_active)
            DrawTextPro(drawFont, m_text.c_str(), m_position, origin, 0.f, m_fontSize, m_spacing, m_color);
    }

    void Label::SetFontFilter(TextureFilter filter)
    {
        if (!m_font)
        {
            TraceLog(LOG_WARNING, "Failed to set font filter because no font set for label!");
            return;
        }

        SetTextureFilter(m_font->texture, filter);
    }
}

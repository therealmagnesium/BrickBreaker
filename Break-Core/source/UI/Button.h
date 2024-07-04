#pragma once
#include "Core/Base.h"
#include "UI/Label.h"
#include <raylib.h>
#include <string>

namespace Break::UI
{
    class Button
    {
    public:
        Button();

        void Update();
        void Draw();

    public:
        inline bool IsHovered() { return m_hovered; }
        inline bool IsClicked() { return m_clicked; }
        inline Vector2& GetScale() { return m_scale; }
        inline Label& GetLabel() { return m_label; }

        inline void SetTexture(Texture2D* texture) { m_texture = texture; }
        inline void SetHoverColor(const Color& color) { m_hoverColor = color; }
        inline void SetPosition(float x, float y) { m_position = {x, y}; }
        inline void SetScale(float x, float y) { m_scale = {x, y}; }

    private:
        void UpdateBody();

    private:
        bool m_hovered = false;
        bool m_clicked = false;

        Vector2 m_position;
        Vector2 m_scale;
        Label m_label;
        Rectangle m_body;

        Color m_hoverColor = RAYWHITE;
        Color m_clickedColor = LIGHTGRAY;
        Texture2D* m_texture = NULL;
    };
}

#include "Scene/Button.h"
#include "Core/Application.h"
#include "raylib.h"

namespace Break::Play
{
    Button::Button()
    {
        m_position = {0.f, 0.f};
        m_scale = {1.f, 1.f};

        m_label.SetSpacing(4.f);
        m_label.SetText("");
        m_label.SetColor(RAYWHITE);
        m_label.SetFontSize(50);
    }

    void Button::Update()
    {
        this->UpdateBody();
        m_clicked = false;
        m_hovered = CheckCollisionPointRec(GetMousePosition(), m_body);

        if (m_hovered)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                m_clicked = true;
        }
    }

    void Button::Draw()
    {
        if (m_texture)
        {
            Rectangle source;
            source.x = 0.f;
            source.y = 0.f;
            source.width = m_texture->width;
            source.height = m_texture->height;

            Rectangle dest;
            dest.x = m_position.x;
            dest.y = m_position.y;
            dest.width = source.width * m_scale.x;
            dest.height = source.height * m_scale.y;

            Vector2 origin;
            origin.x = (m_texture->width * m_scale.x) / 2.f;
            origin.y = (m_texture->height * m_scale.y) / 2.f;

            if (m_hovered)
            {
                if (m_clicked)
                    DrawTexturePro(*m_texture, source, dest, origin, 0.f, m_clickedColor);
                else
                    DrawTexturePro(*m_texture, source, dest, origin, 0.f, m_hoverColor);
            }
            else
                DrawTexturePro(*m_texture, source, dest, origin, 0.f, WHITE);
        }

        m_label.SetPosition(m_position.x, m_position.y);
        m_label.Draw();
    }

    void Button::UpdateBody()
    {
        if (m_texture)
        {
            float xOffset = (m_texture->width * m_scale.x) / 2.f;
            float yOffset = (m_texture->height * m_scale.y) / 2.f;
            m_body.x = m_position.x - xOffset;
            m_body.y = m_position.y - yOffset;
            m_body.width = m_texture->width * m_scale.x;
            m_body.height = m_texture->height * m_scale.y;
        }
    }
}

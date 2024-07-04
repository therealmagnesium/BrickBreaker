#include "UI/CanvasContext.h"
#include "UI/Label.h"
#include "UI/Button.h"
#include "UI/Slider.h"

namespace Break::UI
{
    void CanvasContext::SetLabelCount(u32 labelCount) { labels.resize(labelCount); }
    void CanvasContext::SetButtonCount(u32 buttonCount) { buttons.resize(buttonCount); }
    void CanvasContext::SetSliderCount(u32 sliderCount) { sliders.resize(sliderCount); }

    void CanvasContext::UpdateUIElements()
    {
        for (Button& button : buttons)
            button.Update();

        for (Slider& slider : sliders)
            slider.Update();
    }

    void CanvasContext::DrawUIElements()
    {
        for (Label& label : labels)
            label.Draw();

        for (Button& button : buttons)
            button.Draw();

        for (Slider& slider : sliders)
            slider.Draw();
    }
}

#pragma once
#include "UI/Label.h"
#include "UI/Button.h"
#include "UI/Slider.h"
#include "Core/Base.h"

#include <vector>

namespace Break::UI
{
    struct CanvasContext
    {
        std::vector<Label> labels;
        std::vector<Button> buttons;
        std::vector<Slider> sliders;

        CanvasContext() = default;

        void SetLabelCount(u32 labelCount);
        void SetButtonCount(u32 buttonCount);
        void SetSliderCount(u32 sliderCount);

        void UpdateUIElements();
        void DrawUIElements();
    };
}

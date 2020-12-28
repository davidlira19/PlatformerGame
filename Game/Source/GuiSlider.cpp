#include "GuiSlider.h"
#include "Log.h"

GuiSlider::GuiSlider(int id, SDL_Rect bounds, const char* text, unsigned int clickedFx, unsigned int focusedFx, SDL_Texture* textureButton) : GuiControl(GuiControlType::SLIDER, id)
{
    this->bounds = bounds;
    this->text = text;
    minValue = 0;
    maxValue = 100;
}

GuiSlider::~GuiSlider()
{
}

bool GuiSlider::Update(float dt)
{

    LOG("%d", value);
    if (state != GuiControlState::DISABLED)
    {
        int mouseX, mouseY;
        app->input->GetMousePosition(mouseX, mouseY);
        mouseX += app->render->camera.x * -1;
        mouseY += app->render->camera.y * -1;

        // Check collision between mouse and button bounds
        if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
            (mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
        {
            state = GuiControlState::FOCUSED;
            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
                value = ((maxValue - minValue) * (mouseX - (float)(bounds.x + slider.w / 2))) / (float)(bounds.w - slider.w) + minValue;
              
                if (slider.w > 0)
                {
                    slider.x = mouseX - slider.w / 2;
                }
                else if (slider.w == 0)
                {
                    //slider.w = sliderValue;
                }
            }
        }
        else state = GuiControlState::NORMAL;

        if (value > maxValue)
        {
            value = maxValue;
        }
        else if (value < minValue)
        {
            value = minValue;
        }
    }
    return false;
}

bool GuiSlider::Draw()
{
    // Draw the right button depending on state
    switch (state)
    {
    case GuiControlState::DISABLED: app->render->DrawRectangle(bounds,  100, 100, 100, 255 );
        break;
    case GuiControlState::NORMAL: app->render->DrawRectangle(bounds,  0, 255, 0, 255 );
        break;
    case GuiControlState::FOCUSED: app->render->DrawRectangle(bounds,  255, 255, 0, 255 );
        break;
    case GuiControlState::PRESSED: app->render->DrawRectangle(bounds,  0, 255, 255, 255 );
        break;
    case GuiControlState::SELECTED: app->render->DrawRectangle(bounds, 0, 255, 0, 255 );
        break;
    default:
        break;
    }

    return false;
}

int GuiSlider::GetValue()
{
    return value;
}
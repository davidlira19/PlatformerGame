#include "GuiSlider.h"
#include "Log.h"
#include "Audio.h"

GuiSlider::GuiSlider(int id, SDL_Rect bounds, const char* text, unsigned int clickedFx, unsigned int focusedFx, SDL_Texture* textureButton, SDL_Texture* textureSlider) : GuiControl(GuiControlType::SLIDER, id)
{
    this->bounds = bounds;
    this->text = text;
    minValue = 0;
    maxValue = 100;
	focusedFX = focusedFx;
	clickedFX = clickedFx;
	textureButtons = textureButton;
    textureSliders = textureSlider;
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
				
				NotifyObserver();
              
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
    SDL_Rect rect = { 3486,3838,359,57 };
    SDL_Rect rect2 = { 3450,3955, 3.41 * value,46 };
    SDL_Rect rect3;
	
    if (id == 1)
    {
        rect3 = { 1074,921, 91,96 };
    }
    if (id == 2)
    {
        rect3 = { 1074,1029, 91,96 };
    }
    // Draw the right button depending on state
    switch (state)
    {
    case GuiControlState::DISABLED:
        app->render->DrawTexture(textureSliders, bounds.x, bounds.y, &rect);
        app->render->DrawTexture(textureSliders, bounds.x + 8, bounds.y + 6, &rect2);
        app->render->DrawTexture(textureButtons, bounds.x - 95, bounds.y, &rect3);
        break;
    case GuiControlState::NORMAL:
        app->render->DrawTexture(textureSliders, bounds.x, bounds.y, &rect);
        app->render->DrawTexture(textureSliders, bounds.x + 8, bounds.y + 6, &rect2);
        app->render->DrawTexture(textureButtons, bounds.x - 95, bounds.y, &rect3);
        break;
    case GuiControlState::FOCUSED:
        app->render->DrawTexture(textureSliders, bounds.x, bounds.y, &rect);
        app->render->DrawTexture(textureSliders, bounds.x + 8, bounds.y + 6, &rect2);
        app->render->DrawTexture(textureButtons, bounds.x - 95, bounds.y, &rect3);
        break;
    case GuiControlState::PRESSED:
        app->render->DrawTexture(textureSliders, bounds.x, bounds.y, &rect);
        app->render->DrawTexture(textureSliders, bounds.x + 8, bounds.y + 6, &rect2);
        app->render->DrawTexture(textureButtons, bounds.x - 95, bounds.y, &rect3);
        break;
        break;
    default:
        break;
    }

    return false;
}

int GuiSlider::GetMusicValue()
{
    return value;
}

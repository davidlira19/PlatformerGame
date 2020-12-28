#include "GuiCheckBox.h"
#include "Audio.h"
#include "Window.h"

GuiCheckBox::GuiCheckBox(int id, SDL_Rect bounds, const char* text, unsigned int clickedFx, unsigned int focusedFx, SDL_Texture* textureButton) : GuiControl(GuiControlType::CHECKBOX, id)
{
    this->bounds = bounds;
    this->text = text;
    focusedFX = focusedFx;
    clickedFX = clickedFx;
    textureButtons = textureButton;
}

GuiCheckBox::~GuiCheckBox()
{
}

bool GuiCheckBox::Update( float dt)
{
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
            if (state != GuiControlState::FOCUSED && state != GuiControlState::PRESSED)
            {
                app->audio->PlayFx(focusedFX);
            }
            state = GuiControlState::FOCUSED;

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
            }

            // If mouse button pressed -> Generate event!
            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
            {
                app->audio->PlayFx(clickedFX);
                checked = !checked;
                NotifyObserver();
            }
        }
        else state = GuiControlState::NORMAL;
    }

    

    return false;
}

bool GuiCheckBox::Draw()
{
    SDL_Rect rect;
    SDL_Rect rect2;
    SDL_Rect rect3;
    SDL_Rect rect4;
    SDL_Rect rect5;
    SDL_Rect rect6;
    SDL_Rect rect7;
    SDL_Rect rect8;
    if (id == 8)
    {
        rect = { 297,1360,91,96 };
        rect2 = { 403,1360,91,96 };
        rect3 = { 507,1360,91,96 };
        rect4 = { 613,1360,91,96 };
        rect5 = { 1546,376,91,96 };
        rect6 = { 1648,376,91,96 };
        rect7 = { 1752,376,91,96 };
        rect8 = { 1853,376,91,96 };
    }

    // Draw the right button depending on state
    switch (state)
    {
    case GuiControlState::DISABLED:
    {
        if (checked) 	app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect8);
        else 	app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect4);
    } break;
    case GuiControlState::NORMAL: 
    {
        if (checked) 	app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect5);
        else 	app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect);
    } break;
    case GuiControlState::FOCUSED: 	
    {
        if (checked) 	app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect6);
        else 	app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect2);
    } break;
    case GuiControlState::PRESSED: 	
    {
        if (checked) 	app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect7);
        else 	app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect3);
    } break;
    default:
        break;
    }

    return false;
}

int GuiCheckBox::GetMusicValue()
{
    return 0;
}
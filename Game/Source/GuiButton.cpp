#include "GuiButton.h"

GuiButton::GuiButton(int id, SDL_Rect bounds, const char* text) : GuiControl(GuiControlType::BUTTON, id)
{
    textureButtons = app->tex->Load("Assets/Textures/buttons.png");
    this->bounds = bounds;
    this->text = text;
}

GuiButton::~GuiButton()
{

}

bool GuiButton::Update( float dt)
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
            state = GuiControlState::FOCUSED;

            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
            {
                state = GuiControlState::PRESSED;
            }

            // If mouse button pressed -> Generate event!
            if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
            {
                NotifyObserver();
            }
        }
        else state = GuiControlState::NORMAL;
    }

    return false;
}

bool GuiButton::Draw()
{
    // Draw the right button depending on state
    SDL_Rect rect = { 771,213,213,99 };
    SDL_Rect rect2 = { 86,213,213,99 };
    SDL_Rect rect3 = { 314,213,213,99 };
    SDL_Rect rect4 = { 543,213,213,99 };

    switch (state)
    {
    case GuiControlState::DISABLED: 
		//app->render->DrawRectangle(bounds, 0, 255, 0, 255);
        app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect);
        break;
    case GuiControlState::NORMAL: 
		//app->render->DrawRectangle(bounds,  0, 255, 0, 255 );
       
        app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect2);
        break;
    case GuiControlState::FOCUSED: 
		//app->render->DrawRectangle(bounds,  255, 255, 0, 255 );
        
        app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect3);
        break;
    case GuiControlState::PRESSED:
		//app->render->DrawRectangle(bounds,  0, 255, 255, 255 );
        
        app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect4);
        break;
    case GuiControlState::SELECTED: 
		app->render->DrawRectangle(bounds,  0, 255, 0, 255 );
        break;
    default:
        break;
    }

    return false;
}

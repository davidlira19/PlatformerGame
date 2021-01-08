#include "GuiButton.h"

GuiButton::GuiButton(int id, SDL_Rect bounds, const char* text,unsigned int clickedFx, unsigned int focusedFx, SDL_Texture* textureButton) : GuiControl(GuiControlType::BUTTON, id)
{
	
	this->bounds = bounds;
	this->text = text;
	buttonsColliders = false;
	focusedFX = focusedFx;
	clickedFX = clickedFx;
	textureButtons = textureButton;
	pendingToDelete = false;
}

GuiButton::~GuiButton()
{

}

bool GuiButton::Update( float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		if (buttonsColliders == false)
		{
			buttonsColliders = true;
		}
		else
		{
			buttonsColliders = false;
		}
	}

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
			if (state != GuiControlState::FOCUSED&& state != GuiControlState::PRESSED)
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
				NotifyObserver();
			}
		}
		else state = GuiControlState::NORMAL;
	}

	return false;
}

bool GuiButton::Draw()
{
	SDL_Rect rect;
	SDL_Rect rect2;
	SDL_Rect rect3;
	SDL_Rect rect4;
	if (id == 1)
	{
		rect = { 771,213,213,99 };
		rect2 = { 86,213,213,99 };
		rect3 = { 314,213,213,99 };
		rect4 = { 543,213,213,99 };
	}
	if (id == 2)
	{
		rect = { 771,336,213,99 };
		rect2 = { 86,336,213,99 };
		rect3 = { 314,336,213,99 };
		rect4 = { 543,336,213,99 };
	}
	if (id == 3)
	{
		rect = { 771,925,213,99 };
		rect2 = { 86,925,213,99 };
		rect3 = { 314,925,213,99 };
		rect4 = { 543,925,213,99 };		
	}
	if (id == 4)
	{
		rect = { 771,570,213,99 };
		rect2 = { 86,570,213,99 };
		rect3 = { 314,570,213,99 };
		rect4 = { 543,570,213,99 };
	}
	if (id == 5)
	{
		rect = { 771,690,213,99 };
		rect2 = { 86,690,213,99 };
		rect3 = { 314,690,213,99 };
		rect4 = { 543,690,213,99 };
		
	}
	if (id == 6)
	{
		rect = { 771,808,213,99 };
		rect2 = { 86,808,213,99 };
		rect3 = { 314,808,213,99 };
		rect4 = { 543,808,213,99 };
		
	}
	if (id == 7)
	{
		
		rect = { 771,1045,213,99 };
		rect2 = { 86,1045,213,99 };
		rect3 = { 314,1045,213,99 };
		rect4 = { 543,1045,213,99 };
	}

	switch (state)
	{
	case GuiControlState::DISABLED:
		app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect);
		if (buttonsColliders == true)
		{
			app->render->DrawRectangle(bounds, 0, 255, 0, 255);
		}
		
		
		break;
	case GuiControlState::NORMAL:
		app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect2);
		if (buttonsColliders == true)
		{
			app->render->DrawRectangle(bounds,  0, 255, 0, 255 );
		}
		

		
		break;
	case GuiControlState::FOCUSED:
		app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect3);
		if (buttonsColliders == true)
		{
			app->render->DrawRectangle(bounds,  255, 255, 0, 255 );
		}
		

		
		break;
	case GuiControlState::PRESSED:
		app->render->DrawTexture(textureButtons, bounds.x, bounds.y, &rect4);
		if (buttonsColliders == true)
		{
			app->render->DrawRectangle(bounds,  0, 255, 255, 255 );
		}
		
		
		break;
	case GuiControlState::SELECTED:
		app->render->DrawRectangle(bounds, 0, 255, 0, 255);
		break;
	default:
		break;
	}
	return false;
}

int GuiButton::GetMusicValue()
{
	return 0;
}
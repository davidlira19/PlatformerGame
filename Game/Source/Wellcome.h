#ifndef _WELLCOME_H_
#define _WELLCOME_H_

#include"SDL_image/include/SDL_image.h"
#include"FadeToBlack.h"
#include"Module.h"
#include"App.h"
#include"Render.h"
#include"Textures.h"
#include"Input.h"
#include"GuiManager.h"

class Wellcome :public Module {
public:
	Wellcome(bool startEnabled) : Module(startEnabled)
	{
		toExit = false;

	}

	// Destructor
	virtual ~Wellcome()
	{

	}

	// Called before render is available
	bool Awake()
	{

		return true;
	}

	// Called before the first frame
	bool Start()
	{
		wellcome = app->tex->Load("Assets/Textures/title_screen.png");
		textureCredits = app->tex->Load("Assets/Textures/credits.png");

		SDL_Rect rect = { 525,100,200,81 };
		start = app->gui->CreateGuiControl(GuiControlType::BUTTON, 1, rect, "START");
		start->SetObserver(this);

		rect = { 525,200,200,81 };
		exit = app->gui->CreateGuiControl(GuiControlType::BUTTON, 2, rect, "EXIT");
		exit->SetObserver(this);

		rect = { 525,300,200,81 };
		credits = app->gui->CreateGuiControl(GuiControlType::BUTTON, 3, rect, "CREDITS");
		credits->SetObserver(this);
		return true;
	}
	bool OnGuiMouseClickEvent(GuiControl* control)
	{
		if (control == start)
		{
			app->fade->FadeToBlack(this, (Module*)app->sceneLevel1, 60);
		}
		if (control == exit)
		{
			toExit = true;
		}
		if (control == credits)
		{
			creditsCondition = true;
		}

		return true;
	}


	// Called each loop iteration

	// Called before all Updates
	bool PostUpdate()override
	{
		bool ret = true;
		/*if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			app->fade->FadeToBlack(this, (Module*)app->sceneLevel1, 60);
		}*/
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || toExit == true)
		{
			ret = false;
		}

		app->render->DrawTexture(wellcome, 0, 0);

		if (creditsCondition == true)
		{
			if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
			{
				creditsCondition = false;
				app->tex->UnLoad(wellcome);
				app->fade->FadeToBlack(this, (Module*)app->wellcome, 60);
			}
			app->gui->DestroyAllGuiControl();
			app->render->DrawTexture(textureCredits, 0, 0);
		}

		return ret;
	}

	// Called before quitting
	bool CleanUp()
	{
		app->gui->DestroyAllGuiControl();
		app->tex->UnLoad(wellcome);
		return true;
	}
private:
	SDL_Texture* wellcome;
	SDL_Texture* textureCredits;
	GuiControl* start;
	GuiControl* exit;
	GuiControl* credits;

	bool creditsCondition = false;
	bool toExit;
};
#endif
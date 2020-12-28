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

class Welcome :public Module {
public:
	Welcome(bool startEnabled) : Module(startEnabled)
	{
		toExit = false;

	}

	// Destructor
	virtual ~Welcome()
	{

	}

	// Called before render is available
	bool Awake()
	{

		return true;
	}
	bool isNewGame()
	{
		int x, y;
		pugi::xml_document LoadFile;
		pugi::xml_node load;
		LoadFile.load_file("save_game.xml");
		load = LoadFile.child("game_state");
		pugi::xml_node nodo = load.child("player");
		x = nodo.child("data").attribute("x").as_int();
		y = nodo.child("data").attribute("y").as_int();
		if (x == 1150 && y == 560)
		{
			return true;
		}
		else {
			return false;
		}


	}
	// Called before the first frame
	bool Start(bool newGame)
	{
		wellcome = app->tex->Load("Assets/Textures/title_screen.png");
		textureCredits = app->tex->Load("Assets/Textures/credits.png");

		SDL_Rect rect = { 500,210,200,81 };
		start = app->gui->CreateGuiControl(GuiControlType::BUTTON, 1, rect, "START");
		start->SetObserver(this);

		rect = { 500,310,200,81 };
		load = app->gui->CreateGuiControl(GuiControlType::BUTTON, 2, rect, "CONTINUE");
		load->SetObserver(this);
		if (isNewGame() == true)
		{
			load->state = GuiControlState::DISABLED;
		}

		rect = { 500,410,200,81 };
		settings = app->gui->CreateGuiControl(GuiControlType::BUTTON, 3, rect, "SETTINGS");
		settings->SetObserver(this);

		rect = { 500,610,200,81 };
		exit = app->gui->CreateGuiControl(GuiControlType::BUTTON, 5, rect, "EXIT");
		exit->SetObserver(this);

		rect = { 500,510,200,81 };
		credits = app->gui->CreateGuiControl(GuiControlType::BUTTON, 4, rect, "CREDITS");
		credits->SetObserver(this);
		return true;
	}
	bool OnGuiMouseClickEvent(GuiControl* control)
	{
		if (control == start)
		{
			app->fade->FadeToBlack(this, (Module*)app->sceneLevel1, 60);
		}
		if (control == load)
		{
			app->sceneLevel1->isEnabled = true;
			app->sceneLevel1->Start(true);
			this->Disable();
		}
		if (control == settings)
		{
			
		}
		if (control == credits)
		{
			creditsCondition = true;
		}
		if (control == exit)
		{
			toExit = true;
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
				app->fade->FadeToBlack(this, (Module*)app->welcome, 60);
			}
			app->gui->DestroyAllGuiControl();
			app->render->DrawTexture(textureCredits, 0, 0);
		}

		return ret;
	}

	// Called before quitting
	bool CleanUp()
	{
		app->gui->Disable();
		app->gui->DestroyAllGuiControl();
		app->tex->UnLoad(wellcome);
		return true;
	}
private:
	SDL_Texture* wellcome;
	SDL_Texture* textureCredits;
	GuiControl* start;
	GuiControl* load;
	GuiControl* settings;
	GuiControl* exit;
	GuiControl* credits;
	
	bool creditsCondition = false;
	bool toExit;
};
#endif
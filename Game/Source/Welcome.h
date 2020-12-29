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
#include "Window.h"
#include "GuiSlider.h"

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
	int Level()
	{
		int level;
		pugi::xml_document LoadFile;
		pugi::xml_node load;
		LoadFile.load_file("save_game.xml");
		load = LoadFile.child("game_state");
		pugi::xml_node nodo = load.child("player");
		level = nodo.child("data").attribute("level").as_int();
		return level;
	}
	// Called before the first frame
	bool Start(bool newGame)
	{
		//app->audio->PlayMusic("Assets/Audio/Music/christmas_music.ogg");
		menu = false;
		app->gui->Enable();
		welcome = app->tex->Load("Assets/Textures/title_screen.png");
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
		}else if (control == load)		
		{
			
			if (Level() == 1) 
			{
				app->sceneLevel1->isEnabled = true;
				app->sceneLevel1->Start(true);
			}else
			{			
				app->sceneLevel2->isEnabled = true;
				app->sceneLevel2->Start(true);
			}
			this->Disable();
			app->gui->Enable();
		}else if (control == settings)	
		{
			menu = true;
			SDL_Rect rect = {720,410,91,96 };
			fullscreen = app->gui->CreateGuiControl(GuiControlType::CHECKBOX, 8, rect, "FULLSCREEN");
			fullscreen->SetObserver(this);
	
			rect = { 720,510,91,96 };
			vsync = app->gui->CreateGuiControl(GuiControlType::CHECKBOX, 9, rect, "VSYNC");
			vsync->SetObserver(this);

			rect = { 820,210,359,57 };
			musicVolume = app->gui->CreateGuiControl(GuiControlType::SLIDER, 1, rect, "MUSIC");
			musicVolume->SetObserver(this);

			rect = { 820,310,359,57 };
			fxVolume = app->gui->CreateGuiControl(GuiControlType::SLIDER, 2, rect, "FX");
			fxVolume->SetObserver(this);
		}else if (control == fullscreen)	
		{
			if (app->win->fullScreenWindow == true)
			{
				app->win->fullScreenWindow = false;
			}
			else
			{
				app->win->fullScreenWindow = true;
			}
		}else if (control == vsync)		
		{
			if (app->maxFPS == 13)
			{
				app->maxFPS = 30;
				app->vsync = true;
			}
			else if (app->maxFPS == 30)
			{
				app->maxFPS = 13;
				app->vsync = false;
			}
		}else if (control == musicVolume)	
		{
			app->audio->volumeMusic = musicVolume->GetMusicValue();
		}else if (control == fxVolume)	
		{
			app->audio->volumeFx = fxVolume->GetMusicValue();
		}else if (control == credits)		
		{
			creditsCondition = true;
		}else if (control == exit)	
		{
			SDL_Quit();
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
			//ret = false;
		}

		app->render->DrawTexture(welcome, 0, 0);

		if (creditsCondition == true)
		{
			if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
			{
				creditsCondition = false;
				app->tex->UnLoad(welcome);
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
		app->gui->DestroyAllGuiControl();
		app->gui->Disable();		
		//app->audio->Disable();
		app->tex->UnLoad(welcome);
		app->tex->UnLoad(textureCredits);
		
		return true;
	}
	bool menu;
private:
	SDL_Texture* welcome;
	SDL_Texture* textureCredits;
	GuiControl* start;
	GuiControl* load;
	GuiControl* settings;
	GuiControl* exit;
	GuiControl* credits;
	GuiControl* fullscreen;
	GuiControl* vsync;
	GuiControl* musicVolume;
	GuiControl* fxVolume;
	
	bool creditsCondition = false;
	bool toExit;
};
#endif
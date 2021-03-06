#ifndef _WIN_H_
#define _WIN_H_

#include"SDL_image/include/SDL_image.h"
#include"FadeToBlack.h"
#include"Module.h"
#include"App.h"
#include"Render.h"
#include"Textures.h"
#include"Welcome.h"
#include"Audio.h"

class Win :public Module {
public:
	Win(bool startEnabled) : Module(startEnabled)
	{
	}

	// Destructor
	virtual ~Win()
	{
	}

	// Called before render is available
	bool Awake()
	{
		return true;
	}

	// Called before the first frame
	bool Start(bool newGame)
	{
		//app->audio->Enable();
		//app->gui->Enable();
		app->audio->PlayMusic("Assets/Audio/Music/victory_song.ogg");
		winScreen = app->tex->Load("Assets/Textures/win_screen.png");
		SDL_Rect rect = { 500,400,200,81 };
		nextLevel = app->gui->CreateGuiControl(GuiControlType::BUTTON, 1, rect, "NextLevel");
		nextLevel->SetObserver(this);
		rect = { 500,500,200,81 };
		exit = app->gui->CreateGuiControl(GuiControlType::BUTTON, 5, rect, "exit");
		exit->SetObserver(this);
		return true;
	}

	// Called each loop iteration
	bool Update(float dt)
	{
		return true;
	}

	// Called before all Updates
	bool PostUpdate()
	{
		bool ret = true;
		app->render->DrawTexture(winScreen, 0, 0);
		return ret;
	}
	bool OnGuiMouseClickEvent(GuiControl* control)
	{
		if (control == nextLevel)
		{
			if (app->player->currentLevel == 1)
			{
				app->fade->FadeToBlack(this, (Module*)app->sceneLevel2, 60);
			}
			else
			{
				app->fade->FadeToBlack(this, (Module*)app->welcome, 60);
			}
		}
		else if (control == exit)
		{
			SDL_Quit();
		}

		return true;
	}
	// Called before quitting
	bool CleanUp()
	{

		app->gui->DestroyAllGuiControl();
		//app->gui->Disable();
		app->tex->UnLoad(winScreen);
		return true;
	}
private:
	SDL_Texture* winScreen;
	GuiControl* nextLevel;
	GuiControl* exit;

};
#endif
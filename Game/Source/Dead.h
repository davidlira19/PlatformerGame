#ifndef _DEAD_H_
#define _DEAD_H_

#include"SDL_image/include/SDL_image.h"
#include"FadeToBlack.h"
#include"Module.h"
#include"App.h"
#include"Render.h"
#include"Textures.h"
#include"Welcome.h"

class Dead :public Module {
public:
	Dead(bool startEnabled) : Module(startEnabled) 
	{

	}

	// Destructor
	virtual ~Dead() 
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
		app->audio->PlayMusic("Assets/Audio/Music/dead_song.ogg");
		deadScreen = app->tex->Load("Assets/Textures/dead_screen.png");
		app->gui->Enable();
		SDL_Rect rect = { 500,400,200,81 };
		nextLevel = app->gui->CreateGuiControl(GuiControlType::BUTTON, 1, rect, "NextLevel");
		nextLevel->SetObserver(this);
		rect = { 500,500,200,81 };
		exit = app->gui->CreateGuiControl(GuiControlType::BUTTON, 5, rect, "exit");
		exit->SetObserver(this);
	
		return true;
	}
	bool OnGuiMouseClickEvent(GuiControl* control)
	{
		if (control == nextLevel)
		{
			if (app->player->currentLevel == 1)
			{
				app->fade->FadeToBlack(this, (Module*)app->sceneLevel1, 60);
			}
			else
			{
				app->fade->FadeToBlack(this, (Module*)app->sceneLevel2, 60);
			}
		}
		else if (control == exit)
		{
			SDL_Quit();
		}

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
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			if (app->player->currentLevel == 1)
			{
				app->fade->FadeToBlack(this, (Module*)app->sceneLevel1, 60);
			}
			else if (app->player->currentLevel == 2)
			{
				app->fade->FadeToBlack(this, (Module*)app->sceneLevel2, 60);
			}
		}
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) 
		{
			//ret = false;
		}
			
		app->render->DrawTexture(deadScreen,0,0,0);
		return ret;
	}

	// Called before quitting
	bool CleanUp() 
	{
		app->audio->Unload();
		app->gui->DestroyAllGuiControl();
		app->gui->Disable();
		app->tex->UnLoad(deadScreen);
		//app->audio->Disable();
		return true;
	}
private:
	SDL_Texture* deadScreen;
	GuiControl* nextLevel;
	GuiControl* exit;
};
#endif
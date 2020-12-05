#ifndef _WIN_H_
#define _WIN_H_

#include"SDL_image/include/SDL_image.h"
#include"FadeToBlack.h"
#include"Module.h"
#include"App.h"
#include"Render.h"
#include"Textures.h"
#include"Wellcome.h"
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
	bool Start() 
	{
		winScreen = app->tex->Load("Assets/textures/win_screen.png");
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
				app->fade->FadeToBlack(this, (Module*)app->scene2, 60);
			}
			else 
			{
				app->fade->FadeToBlack(this, (Module*)app->wellcome, 60);
			}
		}
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		{
			ret = false;
		}
		app->render->DrawTexture(winScreen, 0, 0);
		return ret;
	}

	// Called before quitting
	bool CleanUp() 
	{

		app->tex->UnLoad(winScreen);
		return true;
	}
private:
	SDL_Texture* winScreen;

};
#endif
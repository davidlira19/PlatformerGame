#ifndef _DEAD_H_
#define _DEAD_H_

#include"SDL_image/include/SDL_image.h"
#include"FadeToBlack.h"
#include"Module.h"
#include"App.h"
#include"Render.h"
#include"Textures.h"
#include"Wellcome.h"

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
	bool Start() 
	{
		deadScreen = app->tex->Load("Assets/textures/dead_screen.png");
	
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
				app->fade->FadeToBlack(this, (Module*)app->scene, 60);
			}
			else if (app->player->currentLevel == 2)
			{
				app->fade->FadeToBlack(this, (Module*)app->scene2, 60);
			}
		}
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) 
		{
			ret = false;
		}
			
		app->render->DrawTexture(deadScreen,0,0,0);
		return ret;
	}

	// Called before quitting
	bool CleanUp() 
	{

		app->tex->UnLoad(deadScreen);
		return true;
	}
private:
	SDL_Texture* deadScreen;

};
#endif
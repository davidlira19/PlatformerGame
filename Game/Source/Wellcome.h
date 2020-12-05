#ifndef _WELLCOME_H_
#define _WELLCOME_H_

#include"SDL_image/include/SDL_image.h"
#include"FadeToBlack.h"
#include"Module.h"
#include"App.h"
#include"Render.h"
#include"Textures.h"
#include"Input.h"

class Wellcome :public Module {
public:
	Wellcome(bool startEnabled) : Module(startEnabled) {
	
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
		wellcome = app->tex->Load("Assets/textures/title_screen.png");
		return true;
	}



	// Called each loop iteration
	bool Update(float dt)override 
	{
	

		return true;
	}

	// Called before all Updates
	bool PostUpdate()override 
	{
		bool ret = true;
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			app->fade->FadeToBlack(this, (Module*)app->scene, 60);
		}
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		{
			ret = false;
		}
		app->render->DrawTexture(wellcome, 0, 0);
		return ret;
	}

	// Called before quitting
	bool CleanUp() 
	{

		app->tex->UnLoad(wellcome);
		return true;
	}
private:
	SDL_Texture* wellcome;

};
#endif
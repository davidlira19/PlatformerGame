#ifndef _INTRO_H_
#define _INTRO_H_

#include"SDL_image/include/SDL_image.h"
#include"FadeToBlack.h"
#include"Module.h"
#include"App.h"
#include"Render.h"
#include"Textures.h"
#include"Welcome.h"

class Intro :public Module 
{
public:
	Intro(bool startEnabled) : Module(startEnabled) 
	{
		counter = 0;
	}

	// Destructor
	virtual ~Intro() 
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
		intro=app->tex->Load("Assets/Textures/logo_screen.png");
		return true;
	}

	// Called each loop iteration
	bool Update(float dt) 
	{
		counter++;

		return true;
	}

	// Called before all Updates
	bool PostUpdate() 
	{

		if (counter ==150) 
		{
			app->fade->FadeToBlack(this, (Module*)app->welcome, 60);
		}
		app->render->DrawTexture(intro, 0, 0);
		return true;
	}

	// Called before quitting
	bool CleanUp() 
	{

		app->tex->UnLoad(intro);
		return true;
	}
private:
	int counter;
	SDL_Texture* intro;

};
#endif
#include "SceneIntro.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "Player.h"
#include "Input.h"
#include "FadeToBlack.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{

	bool ret = true;

	//app->player->vidas = 3;
	IntroTexture = app->tex->Load("Assets/textures/sceneIntro.png");
	//app->audio->PlayMusic("Assets/audio/music/Christmas_music2004.ogg", 1.0f);
	return ret;
}

bool SceneIntro::Update()
{
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		app->fade->fFadeToBlack(this, (Module*)app->scene, 90);
	}
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		exit(0);
	}
	return true;
}

// Update: draw background
bool SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	SDL_Rect rect = { 0,0,1920,1080 };
	app->render->DrawTexture(IntroTexture, 0, 700, &rect);

	return true;
}
bool SceneIntro::CleanUp()
{

	//app->tex->Unload(IntroTexture);
	app->audio->CleanUp();
	return true;
}
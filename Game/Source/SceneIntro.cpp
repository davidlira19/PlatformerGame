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
	IntroTexture = app->tex->Load("Assets/title_screen.png");
	//app->audio->PlayMusic("Assets/5. How High Can You Get.ogg", 1.0f);
	return ret;
}

bool SceneIntro::Update()
{

	if (app->input->GetKey(SDLK_KP_ENTER) == KEY_DOWN)
	{
		app->fade->Fade(this, (Module*)app->scene, 90);
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
	app->render->DrawTexture(IntroTexture, 0, 0, NULL);
	app->fade->Fade(app->sceneIntro, app->scene, 90.0f);
	return true;
}
bool SceneIntro::CleanUp()
{
	app->tex->UnLoad(IntroTexture);
	app->audio->CleanUp();
	return true;
}
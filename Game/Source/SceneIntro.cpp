#include "SceneIntro.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "Player.h"
#include "Input.h"
#include "FadeToBlack.h"

SceneIntro::SceneIntro() : Module()
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
	//IntroTexture = App->textures->Load("Assets/sceneIntro.png");
	//app->audio->PlayMusic("Assets/5. How High Can You Get.ogg", 1.0f);
	return ret;
}

bool SceneIntro::Update()
{
	/*GamePad& pad = App->input->pads[0];
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->howhigh, 90);
	}
	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_DOWN)
	{
		exit(0);
	}*/
	return true;
}

// Update: draw background
bool SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	//app->render->Blit(IntroTexture, 0, 0, NULL);

	return true;
}
bool SceneIntro::CleanUp()
{

	//app->textures->Unload(IntroTexture);
	//App->audio->CleanUp();
	return true;
}
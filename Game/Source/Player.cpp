#include"App.h"
#include"Player.h"
#include"Render.h"
#include"Textures.h"
#include"Module.h"
#include"Input.h"
#include"Animation.h"
#include"Audio.h"
#include"SDL/include/SDL_scancode.h"

Player::Player() : Module()
{
	//ANIMATION WHEN SANTA IS NOT MOVING
	Stop.PushBack({1153,331,97,152});
	Stop.PushBack({ 73,601,97,152 });
	Stop.PushBack({ 344,601,97,152 });
	Stop.PushBack({ 615,601,97,152 });
	Stop.PushBack({ 887,601,97,152 });
	Stop.PushBack({ 1156,601,97,152 });
	Stop.PushBack({ 75,871,97,152 });
	Stop.PushBack({ 343,871,97,152 });
	Stop.speed = 0.075f;
	Stop.loop = true;

	//ANIMATION WHEN SANTA IS JUMPING
	//ANIMATION WHEN SANTA IS DEAD
	//ANIMATION WHEN SANTA IS RUNNUNG
}
bool Player::Start()
{
	santa = app->tex->Load("Assets/textures/santaanimation.png");
	//SET POSITION
	Position.x = 870; Position.y = 1135;
	currentAnimation = &Stop;
	return true;
}
bool Player::Update()
{
	//INPUT TO MOVE THE PLAYER
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		Position.x -= 2;
	}
	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		Position.x += 2;
	}
	else if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		Position.y -= 2;
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		Position.y += 2;
	}
	return true;
}
bool Player::PostUpdate() {
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(santa, Position.x, Position.y, &rect);
	currentAnimation->Update();
	return true;
}
bool Player::CleanUp() {


	return true;
}
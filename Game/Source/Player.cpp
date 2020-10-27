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

}
bool Player::Start()
{
	santa = app->tex->Load("Assets/textures/santaanimation.png");
	return true;
}
bool Player::Update()
{
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		Posicion.x--;
	}
	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		Posicion.x++;
	}
	else if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		Posicion.y--;
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		Posicion.y++;
	}
	return true;
}
bool Player::PostUpdate() {
	app->render->DrawTexture(santa, Posicion.x, Posicion.y);
	return true;
}
bool Player::CleanUp() {


	return true;
}
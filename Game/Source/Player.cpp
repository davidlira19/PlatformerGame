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
	//ANIMATION WHEN SANTA IS NOT MOVING RIGHT
	Stop.PushBack({ 1082,327,270,156});
	Stop.PushBack({ 1,597,270,156 });
	Stop.PushBack({ 271,597,270,156 });
	Stop.PushBack({ 541,597,270,156 });
	Stop.PushBack({ 811,597,270,156 });
	Stop.PushBack({ 1082,597,270,156 });
	Stop.PushBack({ 1,867,270,156 });
	Stop.PushBack({ 271,867,270,156 });

	//ANIMATION WHEN SANTA IS JUMPING RIGHT
	Stop.PushBack({ 541,867,270,156 });
	Stop.PushBack({ 811,867,270,156 });
	Stop.PushBack({ 1082,867,270,156 });
	Stop.PushBack({ 1,1138,270,156 });
	Stop.PushBack({ 271,1138,270,156 });
	Stop.PushBack({ 541,1138,270,156 });
	Stop.PushBack({ 811,1138,270,156 });
	Stop.PushBack({ 1082,1138,270,156 });

	//ANIMATION WHEN SANTA IS DEAD RIGHT
	Stop.PushBack({ 1,57,270,156 });
	Stop.PushBack({ 271,57,270,156 });
	Stop.PushBack({ 541,57,270,156 });
	Stop.PushBack({ 811,57,270,156 });
	Stop.PushBack({ 1082,57,270,156 });
	Stop.PushBack({ 1,327,270,156 });
	Stop.PushBack({ 271,327,270,156 });
	Stop.PushBack({ 541,327,270,156 });
	Stop.PushBack({ 811,327,270,156 });

	//ANIMATION WHEN SANTA IS RUNNING RIGHT
	Stop.PushBack({ 1,1047,270,156 });
	Stop.PushBack({ 271,1047,270,156 });
	Stop.PushBack({ 541,1047,270,156 });
	Stop.PushBack({ 811,1047,270,156 });
	Stop.PushBack({ 1082,1047,270,156 });
	Stop.PushBack({ 1,1678,270,156 });

	//ANIMATION WHEN SANTA IS NOT MOVING LEFT
	Stop.PushBack({ 1351,327,270,156 });
	Stop.PushBack({ 2431,597,270,156 });
	Stop.PushBack({ 2162,597,270,156 });
	Stop.PushBack({ 1891,597,270,156 });
	Stop.PushBack({ 1621,597,270,156 });
	Stop.PushBack({ 1351,597,270,156 });
	Stop.PushBack({ 2432,867,270,156 });
	Stop.PushBack({ 2162,867,270,156 });

	//ANIMATION WHEN SANTA IS JUMPING LEFT
	Stop.PushBack({ 1891,867,270,156 });
	Stop.PushBack({ 1621,867,270,156 });
	Stop.PushBack({ 1351,867,270,156 });
	Stop.PushBack({ 2432,1138,270,156 });
	Stop.PushBack({ 2162,1138,270,156 });
	Stop.PushBack({ 1891,1138,270,156 });
	Stop.PushBack({ 1621,1138,270,156 });
	Stop.PushBack({ 1351,1138,270,156 });

	//ANIMATION WHEN SANTA IS DEAD LEFT
	Stop.PushBack({ 2431,57,270,156 });
	Stop.PushBack({ 2162,57,270,156 });
	Stop.PushBack({ 1891,57,270,156 });
	Stop.PushBack({ 1621,57,270,156 });
	Stop.PushBack({ 1351,57,270,156 });
	Stop.PushBack({ 2431,327,270,156 });
	Stop.PushBack({ 2162,327,270,156 });
	Stop.PushBack({ 1891,327,270,156 });
	Stop.PushBack({ 1621,327,270,156 });

	//ANIMATION WHEN SANTA IS RUNNING LEFT
	Stop.PushBack({ 2431,1047,270,156 });
	Stop.PushBack({ 2162,1047,270,156 });
	Stop.PushBack({ 1891,1047,270,156 });
	Stop.PushBack({ 1621,1047,270,156 });
	Stop.PushBack({ 1351,1047,270,156 });
	Stop.PushBack({ 2431,1678,270,156 });

	Stop.speed = 0.020f;
	Stop.loop = true;
}
bool Player::Start()
{

	santa = app->tex->Load("Assets/textures/santaanimation.png");
	//SET POSITION
	Position.x = 870; Position.y = 1135;
	currentAnimation = &Stop;

	return true;
}
bool Player::Update(float dt)
{
	//INPUT TO MOVE THE PLAYER
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		//currentAnimation = &Run_Right;
		Position.x += 2;
	}
	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		//currentAnimation = &Run_Left;
		Position.x -= 2;
	}
	else if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		Position.y -= 2;
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		Position.y += 2;
	}
	else if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		currentAnimation = &Jump;
		JumpFunction();
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

//PLAYER FUNCTIONS
void Player::JumpFunction()
{
	
}
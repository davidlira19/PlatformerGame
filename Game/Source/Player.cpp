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
	StopRight.PushBack({ 1082,327,270,156});
	StopRight.PushBack({ 1,597,270,156 });
	StopRight.PushBack({ 271,597,270,156 });
	StopRight.PushBack({ 541,597,270,156 });
	StopRight.PushBack({ 811,597,270,156 });
	StopRight.PushBack({ 1082,597,270,156 });
	StopRight.PushBack({ 1,867,270,156 });
	StopRight.PushBack({ 271,867,270,156 });

	StopRight.speed = 0.075f;
	StopRight.loop = true;

	//ANIMATION WHEN SANTA IS JUMPING RIGHT
	JumpRight.PushBack({ 541,867,270,156 });
	JumpRight.PushBack({ 811,867,270,156 });
	JumpRight.PushBack({ 1082,867,270,156 });
	JumpRight.PushBack({ 1,1138,270,156 });
	JumpRight.PushBack({ 271,1138,270,156 });
	JumpRight.PushBack({ 541,1138,270,156 });
	JumpRight.PushBack({ 811,1138,270,156 });
	JumpRight.PushBack({ 1082,1138,270,156 });

	JumpRight.speed = 0.075f;
	JumpRight.loop = true;

	//ANIMATION WHEN SANTA IS DEAD RIGHT
	DeadRight.PushBack({ 1,57,270,156 });
	DeadRight.PushBack({ 271,57,270,156 });
	DeadRight.PushBack({ 541,57,270,156 });
	DeadRight.PushBack({ 811,57,270,156 });
	DeadRight.PushBack({ 1082,57,270,156 });
	DeadRight.PushBack({ 1,327,270,156 });
	DeadRight.PushBack({ 271,327,270,156 });
	DeadRight.PushBack({ 541,327,270,156 });
	DeadRight.PushBack({ 811,327,270,156 });

	DeadRight.speed = 0.075f;
	DeadRight.loop = false;

	//ANIMATION WHEN SANTA IS RUNNING RIGHT
	RunRight.PushBack({ 1,1407,260,156 });
	RunRight.PushBack({ 271,1407,260,156 });
	RunRight.PushBack({ 541,1407,260,156 });
	RunRight.PushBack({ 811,1407,260,156 });
	RunRight.PushBack({ 1082,1407,260,156 });

	RunRight.speed = 0.075f;
	RunRight.loop = true;

	//ANIMATION WHEN SANTA IS NOT MOVING LEFT
	StopLeft.PushBack({ 1351,327,270,156 });
	StopLeft.PushBack({ 2431,597,270,156 });
	StopLeft.PushBack({ 2162,597,270,156 });
	StopLeft.PushBack({ 1891,597,270,156 });
	StopLeft.PushBack({ 1621,597,270,156 });
	StopLeft.PushBack({ 1351,597,270,156 });
	StopLeft.PushBack({ 2432,867,270,156 });
	StopLeft.PushBack({ 2162,867,270,156 });

	StopLeft.speed = 0.075f;
	StopLeft.loop = true;

	//ANIMATION WHEN SANTA IS JUMPING LEFT
	JumpLeft.PushBack({ 1891,867,270,156 });
	JumpLeft.PushBack({ 1621,867,270,156 });
	JumpLeft.PushBack({ 1351,867,270,156 });
	JumpLeft.PushBack({ 2432,1138,270,156 });
	JumpLeft.PushBack({ 2162,1138,270,156 });
	JumpLeft.PushBack({ 1891,1138,270,156 });
	JumpLeft.PushBack({ 1621,1138,270,156 });
	JumpLeft.PushBack({ 1351,1138,270,156 });

	JumpLeft.speed = 0.075f;
	JumpLeft.loop = true;

	//ANIMATION WHEN SANTA IS DEAD LEFT
	DeadLeft.PushBack({ 2431,57,270,156 });
	DeadLeft.PushBack({ 2162,57,270,156 });
	DeadLeft.PushBack({ 1891,57,270,156 });
	DeadLeft.PushBack({ 1621,57,270,156 });
	DeadLeft.PushBack({ 1351,57,270,156 });
	DeadLeft.PushBack({ 2431,327,270,156 });
	DeadLeft.PushBack({ 2162,327,270,156 });
	DeadLeft.PushBack({ 1891,327,270,156 });
	DeadLeft.PushBack({ 1621,327,270,156 });

	DeadLeft.speed = 0.075f;
	DeadLeft.loop = false;

	//ANIMATION WHEN SANTA IS RUNNING LEFT
	RunLeft.PushBack({ 2431,1407,260,156 });
	RunLeft.PushBack({ 2162,1407,260,156 });
	RunLeft.PushBack({ 1891,1407,260,156 });
	RunLeft.PushBack({ 1621,1407,260,156 });
	RunLeft.PushBack({ 1351,1407,260,156 });
	
	RunLeft.speed = 0.075f;
	RunLeft.loop = true;

}
bool Player::Start()
{

	santa = app->tex->Load("Assets/textures/santa_animation.png");
	//SET POSITION
	Position.x = 870; Position.y = 1125;
	currentAnimation = &StopRight;
	//INITIALIZE VARIABLES
	isJumping = false;
	collider = { Position.x,Position.y,160,156 };
	return true;
}
void Player::updatePosition()
{
	collider.x = Position.x;
	collider.y = Position.y;
}
bool Player::Update(float dt)
{
	//270, 156
	collisionPosition result;
	
	
	//INPUT TO MOVE THE PLAYER
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		lastanimation = currentAnimation;
		currentAnimation = &RunRight;

		Position.x += 2;
	}
	else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		lastanimation = currentAnimation;
		currentAnimation = &RunLeft;

		Position.x -= 2;
	}

	if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		Position.y -= 2;
	}
	else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		Position.y += 2;
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		JumpFunction();
	}

	//JUST UPDATE THE ANIMATION
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		lastanimation = currentAnimation;
		currentAnimation = &StopRight;
	}
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		lastanimation = currentAnimation;
		currentAnimation = &StopLeft;
	}
	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		if (currentAnimation == &RunRight || currentAnimation == &StopRight || currentAnimation == &JumpRight)
		{
			lastanimation = currentAnimation;
			currentAnimation = &DeadRight;
		}
		if (currentAnimation == &RunLeft || currentAnimation == &StopLeft || currentAnimation == &JumpLeft)
		{
			lastanimation = currentAnimation;
			currentAnimation = &DeadLeft;
		}
	}
	updatePosition();
	result = playerCollisions.getCollision(Position, collider, 61);
	if (result == collisionPosition::down)
	{
		Position.y -= 2;
	}
	else if (result == collisionPosition::right)
	{
		Position.x -= 2;
	}
	else if (result == collisionPosition::left) {
		Position.x += 2;
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
	isJumping = true;

	for (int i = 0; i < 100; i++)
	{
		if ((lastanimation == &RunLeft || lastanimation == &StopLeft) && isJumping == true)
		{
			lastanimation = currentAnimation;
			currentAnimation = &JumpLeft;
		}
		if ((lastanimation == &RunRight || lastanimation == &StopRight) && isJumping == true)
		{
			lastanimation = currentAnimation;
			currentAnimation = &JumpRight;
		}
	}
	isJumping = false;
}
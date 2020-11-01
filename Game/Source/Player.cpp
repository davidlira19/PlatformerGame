#include"App.h"
#include"Player.h"
#include"Render.h"
#include"Textures.h"
#include"Module.h"
#include"Input.h"
#include"Animation.h"
#include"Audio.h"
#include "Log.h"
#include"SDL/include/SDL_scancode.h"

Player::Player(bool startEnabled) : Module(startEnabled)
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

	DeadRight.speed = 0.075f;
	DeadRight.loop = true;

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
	DeadLeft.loop = true;

	//ANIMATION WHEN SANTA IS RUNNING LEFT
	RunLeft.PushBack({ 2431,1407,260,156 });
	RunLeft.PushBack({ 2162,1407,260,156 });
	RunLeft.PushBack({ 1891,1407,260,156 });
	RunLeft.PushBack({ 1621,1407,260,156 });
	RunLeft.PushBack({ 1351,1407,260,156 });
	
	RunLeft.speed = 0.075f;
	RunLeft.loop = true;
	name.Create("player");
}
bool Player::Start()
{
	result = collisionPosition::null;
	Intro = true;
	godMode = false;
	//LOAD TEXTURES
	santa = app->tex->Load("Assets/textures/santa_animation.png");
	WinTex = app->tex->Load("Assets/textures/win_screen.png");
	DeadTex = app->tex->Load("Assets/textures/dead_screen.png");
	IntroTex = app->tex->Load("Assets/textures/title_screen.png");
	jumpFx = app->audio->LoadFx("Assets/audio/fx/santa_jump.ogg");
	landFx = app->audio->LoadFx("Assets/audio/fx/santa_land.wav");
	//SET POSITION
	Position.x = 870; Position.y = 1125;
	currentAnimation = &StopRight;
	//INITIALIZE VARIABLES
	isJumping = false;

	canMove = false;

	Win = false;
	Dead = false;

	aceleration = 10.0f;
	velocity = 0;

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
	updatePosition();

	if (godMode == false)
	{
		result = playerCollisions.getCollision(Position, collider, 61);
		if (result == collisionPosition::down)
		{
			if (((currentAnimation == &JumpLeft) || (currentAnimation == &StopLeft) || (currentAnimation == &StopRight) || (currentAnimation == &JumpRight)) && (velocity > 0)) 
			{
				app->audio->PlayFx(landFx);
			}
			if (state == playerState::jumping)
			{
				JumpFunction();
			}
			else
			{
				if (lastanimation == &JumpLeft) 
				{
					lastanimation = currentAnimation;
					currentAnimation = &StopLeft;
				}
				else if (lastanimation == &JumpRight)
				{
					lastanimation = currentAnimation;
					currentAnimation = &StopRight;
				}
			}
			velocity = 0;
		}
		else
		{
			if (state != playerState::jumping)
			{
				Gravity();
			}
		}
		if (state == playerState::jumping)
		{
			currentAnimation->Update();
			JumpFunction();
		}
		if (result == collisionPosition::right)
		{
			Position.x -= 10;
			Position.y -= 4;
		}
		if (result == collisionPosition::downAndRight)
		{
			Position.x -= 4;
			Position.y -= 4;
		}
		if (result == collisionPosition::downAndLeft)
		{
			Position.x += 4;
			Position.y -= 4;
		}
		else if (result == collisionPosition::left)
		{
			Position.x += 10;
			Position.y -= 4;
		}
	}
	//CONDITIONS TO WIN - LOSE
	if ((Position.y  >= 1602) && (Position.y <= 1608))
	{
		Dead = true;
	}
	if (Position.x >= 9550 && Position.x <= 9560)
	{
		Win = true;
	}
	//LOG("POSITION X: %d --- POSITION Y: %d", Position.x, Position.y);

	//INPUT TO MOVE THE PLAYER
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && canMove == true)
	{
		if ((result) == (collisionPosition::down))
		{
			lastanimation = currentAnimation;
			currentAnimation = &RunRight;
			currentAnimation->Update();
		}
		if (state == playerState::jumping) 
		{
			currentAnimation = &JumpRight;
		}
		app->scene->freeCamera = true;
		Position.x += 4;
		app->render->camera.x -= 4;
	}
	else if ((app->input->GetKey(SDL_SCANCODE_A)) == (KEY_REPEAT) && (canMove == true))
	{
		if ((result) == (collisionPosition::down))
		{
			lastanimation = currentAnimation;
			currentAnimation = &RunLeft;
			currentAnimation->Update();
		}
		if ((state) == (playerState::jumping)) 
		{
			currentAnimation = &JumpLeft;
		}
		Position.x -= 4;
		app->render->camera.x += 4;
	}

	if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (canMove == true))
	{
		if(godMode == true)
		{
			Position.y -= 4;
		}
	}
	else if ((app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (canMove == true))
	{
		if (godMode == true) 
		{
			Position.y += 4;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && canMove == true)
	{
		app->audio->PlayFx(jumpFx);
		if (result == collisionPosition::down) 
		{
			if (currentAnimation == &RunRight || currentAnimation == &StopRight )
			{
				lastanimation = currentAnimation;
				currentAnimation = &JumpRight;
			}
			else if (currentAnimation == &RunLeft || currentAnimation == &StopLeft)
			{
				lastanimation = currentAnimation;
				currentAnimation = &JumpLeft;

			}
			state = playerState::jumping;
			currentAnimation->Update();
		}
		
		//JumpFunction();
	}
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (godMode == false) 
		{
			godMode = true;
		}
		else 
		{
			godMode = false;
		}
	}
	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) 
	{
		app->SaveGameRequest("save_game.xml");
	}
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{
		app->LoadGameRequest("save_game.xml");
	}
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN|| app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		app->player->CleanUp();
		app->scene->CleanUp();
		app->player->Start();
		app->scene->Start();
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
		DeadAction();
	}
	
	return true;
}
bool Player::PostUpdate() 
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(santa, Position.x, Position.y, &rect);

	if (Dead == true)
	{
		DeadAction();
		canMove = false;
		app->scene->freeCamera = false;
		godMode = true;
		app->render->DrawTexture(DeadTex, app->render->camera.x * -1, app->render->camera.y * -1);
	}
	if (Win == true)
	{
		canMove = false;
		app->scene->freeCamera = false;
		app->render->DrawTexture(WinTex, app->render->camera.x * -1, app->render->camera.y * -1);
	}
	if ((Dead == true || Win == true) && (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN))
	{
		app->scene->Start();
		app->player->Start();
	}

	app->render->DrawTexture(IntroTex, app->render->camera.x * -1, app->render->camera.y * -1);
	if (Intro == true && app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		Intro = false;
		app->tex->UnLoad(IntroTex);
		canMove = true;
	}
	
	return true;
}

bool Player::CleanUp() 
{
	app->tex->UnLoad(WinTex);
	app->tex->UnLoad(DeadTex);
	app->tex->UnLoad(santa);

	return true;
}

void Player::Gravity()
{
	velocity += aceleration * 0.05 * 2;
	Position.y += velocity * 0.05 * 2;
	app->render->camera.y -= velocity * 0.05 * 2;
}
//PLAYER FUNCTIONS
void Player::JumpFunction()
{
	collisionPosition result;
	if (jumpingCount < 45)
	{
		if (((lastanimation == &RunLeft) || (lastanimation == &StopLeft)))
		{
			lastanimation = currentAnimation;
			currentAnimation = &JumpLeft;
		}
		if (((lastanimation == &RunRight) || (lastanimation == &StopRight)))
		{
			lastanimation = currentAnimation;
			currentAnimation = &JumpRight;
		}
		Position.y -= 4;
		app->render->camera.y += 4;
		jumpingCount++;
	}
	else 
	{
		result = collisionPosition::null;
		state = playerState::null;
		jumpingCount = 0;
		Position.y += 4;
		velocity = 3.0f;
	}
}
void Player::DeadAction()
{
	if ((currentAnimation == &RunRight) || (currentAnimation == &StopRight) || (currentAnimation == &JumpRight))
	{
		lastanimation = currentAnimation;
		currentAnimation = &DeadRight;
		currentAnimation->Update();
	}
	else if ((currentAnimation == &RunLeft) || (currentAnimation == &StopLeft) || (currentAnimation == &JumpLeft))
	{
		lastanimation = currentAnimation;
		currentAnimation = &DeadLeft;
		currentAnimation->Update();
	}
}
bool Player::SaveState(pugi::xml_node* nodo)
{
	pugi::xml_node node=nodo->append_child("data");
	node.append_attribute("x").set_value(Position.x);
	node.append_attribute("y").set_value(Position.y);
	node.append_attribute("aceleration") = aceleration;
	
	return true;
}
bool Player::LoadState(pugi::xml_node* nodo)
{
	Position.x = nodo->child("data").attribute("x").as_int();
	Position.y = nodo->child("data").attribute("y").as_int();
	aceleration = nodo->child("data").attribute("aceleration").as_int();
	return true;
}
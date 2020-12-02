#include"App.h"
#include"Player.h"
#include"Render.h"
#include"Textures.h"
#include"Module.h"
#include"Input.h"
#include"Animation.h"
#include"Audio.h"
#include "Log.h"
#include"Map.h"
#include"SDL/include/SDL_scancode.h"
#include"FadeToBlack.h"
#include"Dead.h"
#include"Collisions.h"
Player::Player(bool startEnabled) : Module(startEnabled)
{
	//ANIMATION WHEN SANTA IS NOT MOVING RIGHT
	StopRight.PushBack({ 1082 / 2,327 / 2,270 / 2,156 / 2 });
	StopRight.PushBack({ 1 / 2,597 / 2,270 / 2,156 / 2 });
	StopRight.PushBack({ 271 / 2,597 / 2,270 / 2,156 / 2 });
	StopRight.PushBack({ 541 / 2,597 / 2,270 / 2,156 / 2 });
	StopRight.PushBack({ 811 / 2,597 / 2,270 / 2,156 / 2 });
	StopRight.PushBack({ 1082 / 2,597 / 2,270 / 2,156 / 2 });
	StopRight.PushBack({ 1 / 2,867 / 2,270 / 2,156 / 2 });
	StopRight.PushBack({ 271 / 2,867 / 2,270 / 2,156 / 2 });

	StopRight.speed = 0.2f;
	StopRight.loop = true;

	//ANIMATION WHEN SANTA IS JUMPING RIGHT
	JumpRight.PushBack({ 541 / 2,867 / 2,270 / 2,156 / 2 });
	JumpRight.PushBack({ 811 / 2,867 / 2,270 / 2,156 / 2 });
	JumpRight.PushBack({ 1082 / 2,867 / 2,270 / 2,156 / 2 });
	JumpRight.PushBack({ 1 / 2,1138 / 2,270 / 2,156 / 2 });
	JumpRight.PushBack({ 271 / 2,1138 / 2,270 / 2,156 / 2 });
	JumpRight.PushBack({ 541 / 2,1138 / 2,270 / 2,156 / 2 });
	JumpRight.PushBack({ 811 / 2,1138 / 2,270 / 2,156 / 2 });
	JumpRight.PushBack({ 1082 / 2,1138 / 2,270 / 2,156 / 2 });

	JumpRight.speed = 0.2f;
	JumpRight.loop = true;

	//ANIMATION WHEN SANTA IS DEAD RIGHT
	DeadRight.PushBack({ 1 / 2,57 / 2,270 / 2,156 / 2 });
	DeadRight.PushBack({ 271 / 2,57 / 2,270 / 2,156 / 2 });
	DeadRight.PushBack({ 541 / 2,57 / 2,270 / 2,156 / 2 });
	DeadRight.PushBack({ 811 / 2,57 / 2,270 / 2,156 / 2 });
	DeadRight.PushBack({ 1082 / 2,57 / 2,270 / 2,156 / 2 });
	DeadRight.PushBack({ 1 / 2,327 / 2,270 / 2,156 / 2 });
	DeadRight.PushBack({ 271 / 2,327 / 2,270 / 2,156 / 2 });
	DeadRight.PushBack({ 541 / 2,327 / 2,270 / 2,156 / 2 });

	DeadRight.speed = 0.2f;
	DeadRight.loop = true;

	//ANIMATION WHEN SANTA IS RUNNING RIGHT
	RunRight.PushBack({ 1 / 2,1407 / 2,260 / 2,156 / 2 });
	RunRight.PushBack({ 271 / 2,1407 / 2,260 / 2,156 / 2 });
	RunRight.PushBack({ 541 / 2,1407 / 2,260 / 2,156 / 2 });
	RunRight.PushBack({ 811 / 2,1407 / 2,260 / 2,156 / 2 });
	RunRight.PushBack({ 1082 / 2,1407 / 2,260 / 2,156 / 2 });

	RunRight.speed = 0.2f;
	RunRight.loop = true;

	//ANIMATION WHEN SANTA IS NOT MOVING LEFT
	StopLeft.PushBack({ 1351 / 2,327 / 2,270 / 2,156 / 2 });
	StopLeft.PushBack({ 2431 / 2,597 / 2,270 / 2,156 / 2 });
	StopLeft.PushBack({ 2162 / 2,597 / 2,270 / 2,156 / 2 });
	StopLeft.PushBack({ 1891 / 2,597 / 2,270 / 2,156 / 2 });
	StopLeft.PushBack({ 1621 / 2,597 / 2,270 / 2,156 / 2 });
	StopLeft.PushBack({ 1351 / 2,597 / 2,270 / 2,156 / 2 });
	StopLeft.PushBack({ 2432 / 2,867 / 2,270 / 2,156 / 2 });
	StopLeft.PushBack({ 2162 / 2,867 / 2,270 / 2,156 / 2 });

	StopLeft.speed = 0.2f;
	StopLeft.loop = true;

	//ANIMATION WHEN SANTA IS JUMPING LEFT
	JumpLeft.PushBack({ 1891 / 2,867 / 2,270 / 2,156 / 2 });
	JumpLeft.PushBack({ 1621 / 2,867 / 2,270 / 2,156 / 2 });
	JumpLeft.PushBack({ 1351 / 2,867 / 2,270 / 2,156 / 2 });
	JumpLeft.PushBack({ 2432 / 2,1138 / 2,270 / 2,156 / 2 });
	JumpLeft.PushBack({ 2162 / 2,1138 / 2,270 / 2,156 / 2 });
	JumpLeft.PushBack({ 1891 / 2,1138 / 2,270 / 2,156 / 2 });
	JumpLeft.PushBack({ 1621 / 2,1138 / 2,270 / 2,156 / 2 });
	JumpLeft.PushBack({ 1351 / 2,1138 / 2,270 / 2,156 / 2 });

	JumpLeft.speed = 0.2f;
	JumpLeft.loop = true;

	//ANIMATION WHEN SANTA IS DEAD LEFT
	DeadLeft.PushBack({ 2431 / 2,57 / 2,270 / 2,156 / 2 });
	DeadLeft.PushBack({ 2162 / 2,57 / 2,270 / 2,156 / 2 });
	DeadLeft.PushBack({ 1891 / 2,57 / 2,270 / 2,156 / 2 });
	DeadLeft.PushBack({ 1621 / 2,57 / 2,270 / 2,156 / 2 });
	DeadLeft.PushBack({ 1351 / 2,57 / 2,270 / 2,156 / 2 });
	DeadLeft.PushBack({ 2431 / 2,327 / 2,270 / 2,156 / 2 });
	DeadLeft.PushBack({ 2162 / 2,327 / 2,270 / 2,156 / 2 });
	DeadLeft.PushBack({ 1891 / 2,327 / 2,270 / 2,156 / 2 });
	DeadLeft.PushBack({ 1621 / 2,327 / 2,270 / 2,156 / 2 });

	DeadLeft.speed = 0.2f;
	DeadLeft.loop = true;

	//ANIMATION WHEN SANTA IS RUNNING LEFT
	RunLeft.PushBack({ 2431 / 2,1407 / 2,260 / 2,156 / 2 });
	RunLeft.PushBack({ 2162 / 2,1407 / 2,260 / 2,156 / 2 });
	RunLeft.PushBack({ 1891 / 2,1407 / 2,260 / 2,156 / 2 });
	RunLeft.PushBack({ 1621 / 2,1407 / 2,260 / 2,156 / 2 });
	RunLeft.PushBack({ 1351 / 2,1407 / 2,260 / 2,156 / 2 });
	
	RunLeft.speed = 0.2f;
	RunLeft.loop = true;
	name.Create("player");
}
bool Player::Start()
{
	noise = true;
	cont = 0;
	app->SaveGameRequest("save_game.xml");
	result = collisionPosition::null;
	Intro = true;
	godMode = false;
	lifes = 3;
	points = 0;
	//LOAD TEXTURES
	santa = app->tex->Load("Assets/textures/santa_animation.png");
	WinTex = app->tex->Load("Assets/textures/win_screen.png");
	DeadTex = app->tex->Load("Assets/textures/dead_screen.png");
	IntroTex = app->tex->Load("Assets/textures/title_screen.png");
	jumpFx = app->audio->LoadFx("Assets/audio/fx/santa_jump.ogg");
	landFx = app->audio->LoadFx("Assets/audio/fx/santa_land.wav");
	coinFx = app->audio->LoadFx("Assets/audio/fx/coin_drop.wav");
	lifeFx = app->audio->LoadFx("Assets/audio/fx/life.wav");
	checkpointFx = app->audio->LoadFx("Assets/audio/fx/checkpoint.wav");
	LifesTex = app->tex->Load("Assets/textures/lifes.png");
	//SET POSITION
	Position.x = 2300 / 2; Position.y = 500 / 2;
	//2300
	currentAnimation = &StopRight;
	//INITIALIZE VARIABLES
	isJumping = false;

	canMove = true;

	Win = false;
	Dead = false;

	aceleration = 13.0f;
	velocity = 0;

	collider = { Position.x, Position.y, 42, 76 };
	SDL_Rect rect = { Position.x, Position.y, 43, 1 };
	playerCollider = app->collisions->AddCollider(rect, Collider::PLAYER, (Module*)this);
	rect = { Position.x, Position.y, 1, 74 };
	playerRight = app->collisions->AddCollider(rect, Collider::PLAYERRIGHT , (Module*)this);
	rect = { Position.x, Position.y, 1, 74 };
	playerLeft = app->collisions->AddCollider(rect, Collider::PLAYERLEFT, (Module*)this);
	lateralsR = false;
	lateralsL = false;
	lastPosition = Position;
	return true;
}
//void Player::updatePosition()
//{
//	collider.x = Position.x;
//	collider.y = Position.y;
//}
bool Player::Update(float dt)
{
	//270, 156
	//updatePosition();
	if (Position.x>=2610 && Position.x <= 2620)
	{
		noise = true;
	}
	LOG("%d %d", points, lifes);
	if ((Position.x >= 1000 && Position.x <= 2140 && app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) || (Position.x >= 4900 && Position.x <= 5700 && app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN))
	{
		Position.x = 2141;
		Position.y = 435;
	}
	else if (Position.x >= 2141 && Position.x <= 4903 && app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
	{
		Position.x = 4900;
		Position.y = 563;
	}
	playerCollider->SetPos(Position.x+app->render->camera.x+43, Position.y+app->render->camera.y+76);
	playerRight->SetPos(Position.x + app->render->camera.x + 90, Position.y + app->render->camera.y-2);
	playerLeft->SetPos(Position.x + app->render->camera.x + 40, Position.y + app->render->camera.y - 2);
	if (godMode == false)
	{
		/*result = playerCollisions.getCollision(Position, collider, 61);
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
		}*/
	}
	//CONDITIONS TO WIN - LOSE
	if (Position.y  >= 1602 / 2)
	{
		Dead = true;
	}
	if (Position.x >= 11350 / 2)
	{
		Win = true;
	}

	///////////
	
 
	
	//////////
	//LOG("POSITION X: %d --- POSITION Y: %d", Position.x, Position.y);

	//INPUT TO MOVE THE PLAYER
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && canMove == true)
	{
		if (lateralsR == false) {
	
			if ((state == playerState::null) && (godMode == false))
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
			lastPosition = Position;
		    Position.x += 300* (dt / 1000);
			//////app->render->camera.x -= 300* (dt / 1000);
		}
	}
	else if ((app->input->GetKey(SDL_SCANCODE_A)) == (KEY_REPEAT) && (canMove == true))
	{
		if (lateralsL == false) {
			if (state==playerState::null)
			{
				lastanimation = currentAnimation;
				currentAnimation = &RunLeft;
				currentAnimation->Update();
			}
			if ((state) == (playerState::jumping))
			{
				currentAnimation = &JumpLeft;
			}
			lastPosition = Position;
			Position.x -= 300 * (dt / 1000);
			//////app->render->camera.x += 300 * (dt / 1000);
		}
	}

	if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (canMove == true))
	{
		if(godMode == true)
		{
			Position.y -= 300 * (dt / 1000);
		}
	}
	else if ((app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (canMove == true))
	{
		if (godMode == true) 
		{
			Position.y += 300 * (dt/1000);
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && canMove == true)
	{
		app->audio->PlayFx(jumpFx);
		if (state==playerState::null) 
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
	if (state == playerState::jumping)
	{
		JumpFunction(dt);
	}
	else if (state != playerState::null && state != playerState::jumping)
	{
		Gravity(dt);
	}
	return true;
}
bool Player::PostUpdate() 
{
	
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(santa, Position.x, Position.y, &rect);

	switch (lifes)
	{
	case 3:
		rect = { 0,0,99,49 };
		app->render->DrawTexture(LifesTex,app->render->camera.x*-1, app->render->camera.y*-1, &rect);
		break;
	case 2:
		rect = { 0,0,65,49 };
		app->render->DrawTexture(LifesTex, app->render->camera.x*-1, app->render->camera.y*-1, &rect);
		break;
	case 1:
		rect = { 0,0,32,49 };
		app->render->DrawTexture(LifesTex, app->render->camera.x*-1, app->render->camera.y*-1, &rect);
		break;
	default:
		break;
	}

	if (Dead == true)
	{
		/*DeadAction();
		canMove = false;
		app->scene->freeCamera = false;
		godMode = true;*/
		//app->render->DrawTexture(DeadTex, app->render->camera.x * -1, app->render->camera.y * -1);
		if (lifes != 0)
		{
			Dead = false;
			lifes--;
			app->LoadGameRequest("save_game.xml");
		}
		if (lifes == 0)
		{
			app->fade->FadeToBlack(this, (Module*)app->dead, 50);
			Dead = false;
			canMove = false;
		}
	}
	if (Win == true)
	{
		/*canMove = false;
		app->scene->freeCamera = false;
		app->render->DrawTexture(WinTex, app->render->camera.x * -1, app->render->camera.y * -1);*/
		app->fade->FadeToBlack(this, (Module*)app->winp, 50);
		Win = false;
		canMove = false;
	}
	

	if (state != playerState::jumping) 
	{
		state = playerState::free;
	}
	lateralsR = false;
	lateralsL = false;
	return true;
}

bool Player::CleanUp() 
{
	app->tex->UnLoad(WinTex);
	app->tex->UnLoad(DeadTex);
	app->tex->UnLoad(santa);
	app->tex->UnLoad(IntroTex);
	app->scene->Disable();
	return true;
}

void Player::Gravity(float dt)
{
	lastPosition = Position;
	velocity += aceleration * 0.05 * 100 * (dt / 1000);
	Position.y += velocity * 0.05 * 100 * (dt / 1000);
	app->render->camera.y -= velocity * 0.05 * 100 * (dt/1000);
}
//PLAYER FUNCTIONS
void Player::JumpFunction(float dt)
{
	collisionPosition result;
	if (jumpingCount < 30)
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
		lastPosition = Position;
		Position.y -= 150*(dt/1000);
		app->render->camera.y += 150*(dt/1000);
		jumpingCount+= (dt/15);
		
	}
	else 
	{
		//result = collisionPosition::null;
		lastPosition = Position;
		state = playerState::free;
		jumpingCount = 0;
		Position.y += 3;
		//////app->render->camera.y -= 3;
		velocity = 5.0f;
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
void Player::OnCollision(Collider* c1, Collider* c2) 
{
	if (c1->type == Collider::PLAYER) 
	{
		if (c2->type == Collider::FLOOR) 
		{
			state = playerState::null;
			if (velocity > 80)
			{
				Position.y -= velocity * 0.05 * 2;
				
			}
			velocity = 0;
		}
		else if (c2->type == Collider::COIN)
		{
			points += 100;
			app->audio->PlayFx(coinFx);
			c2->pendingToDelete = true;
		}
		else if (c2->type == Collider::HEARTH)
		{
			points += 50;
			app->audio->PlayFx(lifeFx);
			lifes++;
			c2->pendingToDelete = true;
		}
	
	}
	else if (c1->type == Collider::PLAYERRIGHT) 
	{
		if (c2->type == Collider::FLOOR)
		{
			if (state == playerState::null) 
			{
				//state = playerState::free;
				lateralsR = true;
			}
			else 
			{
			
				lateralsR = true;
			}
			

		}else if (c2->type == Collider::CHECKPOINT)	
		{
			app->SaveGameRequest("save_game.xml");
			if (noise == true)
			{
				app->audio->PlayFx(app->player->checkpointFx);
				noise = false;
			}
		}else if (c2->type == Collider::WALL)		
		{		
			state = playerState::free;
			lateralsR = true;		
		}
		else if (c2->type == Collider::ENEMY2) 
		{
			Dead = true;
			
		}
		else if (c2->type == Collider::COIN)
		{
			points += 100;
			app->audio->PlayFx(coinFx);
			c2->pendingToDelete = true;
		}
		else if (c2->type == Collider::HEARTH)
		{
			points += 50;
			app->audio->PlayFx(lifeFx);
			lifes++;
			c2->pendingToDelete = true;
		}
	}
	else if (c1->type == Collider::PLAYERLEFT)
	{
		if (c2->type == Collider::FLOOR)
		{
			if (state == playerState::null)
			{
				//state = playerState::free;
				lateralsL = true;
			}
			else
			{

				lateralsL = true;
			}


		}else if (c2->type == Collider::WALL)		
		{

			state = playerState::free;
			lateralsL = true;

		}else if (c2->type == Collider::ENEMY2)	
		{
			Dead = true;
			
		}
		else if (c2->type == Collider::COIN)
		{
			points += 100;
			app->audio->PlayFx(coinFx);
			c2->pendingToDelete = true;
		}
		else if (c2->type == Collider::HEARTH)
		{
			points += 50;
			app->audio->PlayFx(lifeFx);
			lifes++;
			c2->pendingToDelete = true;
		}
	}
}
bool Player::HasThePlayerMove() 
{
	iPoint actual, previous;
	actual=app->map->WorldToMap(Position.x, Position.y);
	previous = app->map->WorldToMap(lastPosition.x, lastPosition.y);
	if (actual != previous) 
	{
		return true;
	}
	else {
		return false;
	}

}
iPoint Player:: GetPosition()
{
	iPoint point;
	point.x = Position.x;
	point.y = Position.y;
	return point;
}
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
#include "EntityManager.h"

Player::Player(bool startEnabled) : Module(startEnabled)
{
	//ANIMATION WHEN SANTA IS NOT MOVING RIGHT
	stopRight.PushBack({ 1082 / 2,327 / 2,270 / 2,156 / 2 });
	stopRight.PushBack({ 1 / 2,597 / 2,270 / 2,156 / 2 });
	stopRight.PushBack({ 271 / 2,597 / 2,270 / 2,156 / 2 });
	stopRight.PushBack({ 541 / 2,597 / 2,270 / 2,156 / 2 });
	stopRight.PushBack({ 811 / 2,597 / 2,270 / 2,156 / 2 });
	stopRight.PushBack({ 1082 / 2,597 / 2,270 / 2,156 / 2 });
	stopRight.PushBack({ 1 / 2,867 / 2,270 / 2,156 / 2 });
	stopRight.PushBack({ 271 / 2,867 / 2,270 / 2,156 / 2 });

	stopRight.speed = 0.2f;
	stopRight.loop = true;

	//ANIMATION WHEN SANTA IS JUMPING RIGHT
	jumpRight.PushBack({ 541 / 2,867 / 2,270 / 2,156 / 2 });
	jumpRight.PushBack({ 811 / 2,867 / 2,270 / 2,156 / 2 });
	jumpRight.PushBack({ 1082 / 2,867 / 2,270 / 2,156 / 2 });
	jumpRight.PushBack({ 1 / 2,1138 / 2,270 / 2,156 / 2 });
	jumpRight.PushBack({ 271 / 2,1138 / 2,270 / 2,156 / 2 });
	jumpRight.PushBack({ 541 / 2,1138 / 2,270 / 2,156 / 2 });
	jumpRight.PushBack({ 811 / 2,1138 / 2,270 / 2,156 / 2 });
	jumpRight.PushBack({ 1082 / 2,1138 / 2,270 / 2,156 / 2 });

	jumpRight.speed = 0.12f;
	jumpRight.loop = true;

	//ANIMATION WHEN SANTA IS DEAD RIGHT
	deadRight.PushBack({ 1 / 2,57 / 2,270 / 2,156 / 2 });
	deadRight.PushBack({ 271 / 2,57 / 2,270 / 2,156 / 2 });
	deadRight.PushBack({ 541 / 2,57 / 2,270 / 2,156 / 2 });
	deadRight.PushBack({ 811 / 2,57 / 2,270 / 2,156 / 2 });
	deadRight.PushBack({ 1082 / 2,57 / 2,270 / 2,156 / 2 });
	deadRight.PushBack({ 1 / 2,327 / 2,270 / 2,156 / 2 });
	deadRight.PushBack({ 271 / 2,327 / 2,270 / 2,156 / 2 });
	deadRight.PushBack({ 541 / 2,327 / 2,270 / 2,156 / 2 });

	deadRight.speed = 0.2f;
	deadRight.loop = false;

	//ANIMATION WHEN SANTA IS RUNNING RIGHT
	runRight.PushBack({ 1 / 2,1407 / 2,260 / 2,156 / 2 });
	runRight.PushBack({ 271 / 2,1407 / 2,260 / 2,156 / 2 });
	runRight.PushBack({ 541 / 2,1407 / 2,260 / 2,156 / 2 });
	runRight.PushBack({ 811 / 2,1407 / 2,260 / 2,156 / 2 });
	runRight.PushBack({ 1082 / 2,1407 / 2,260 / 2,156 / 2 });

	runRight.speed = 0.2f;
	runRight.loop = true;

	//ANIMATION WHEN SANTA IS NOT MOVING LEFT
	stopLeft.PushBack({ 1351 / 2,327 / 2,270 / 2,156 / 2 });
	stopLeft.PushBack({ 2431 / 2,597 / 2,270 / 2,156 / 2 });
	stopLeft.PushBack({ 2162 / 2,597 / 2,270 / 2,156 / 2 });
	stopLeft.PushBack({ 1891 / 2,597 / 2,270 / 2,156 / 2 });
	stopLeft.PushBack({ 1621 / 2,597 / 2,270 / 2,156 / 2 });
	stopLeft.PushBack({ 1351 / 2,597 / 2,270 / 2,156 / 2 });
	stopLeft.PushBack({ 2432 / 2,867 / 2,270 / 2,156 / 2 });
	stopLeft.PushBack({ 2162 / 2,867 / 2,270 / 2,156 / 2 });

	stopLeft.speed = 0.2f;
	stopLeft.loop = true;

	//ANIMATION WHEN SANTA IS JUMPING LEFT
	jumpLeft.PushBack({ 1891 / 2,867 / 2,270 / 2,156 / 2 });
	jumpLeft.PushBack({ 1621 / 2,867 / 2,270 / 2,156 / 2 });
	jumpLeft.PushBack({ 1351 / 2,867 / 2,270 / 2,156 / 2 });
	jumpLeft.PushBack({ 2432 / 2,1138 / 2,270 / 2,156 / 2 });
	jumpLeft.PushBack({ 2162 / 2,1138 / 2,270 / 2,156 / 2 });
	jumpLeft.PushBack({ 1891 / 2,1138 / 2,270 / 2,156 / 2 });
	jumpLeft.PushBack({ 1621 / 2,1138 / 2,270 / 2,156 / 2 });
	jumpLeft.PushBack({ 1351 / 2,1138 / 2,270 / 2,156 / 2 });

	jumpLeft.speed = 0.12f;
	jumpLeft.loop = true;

	//ANIMATION WHEN SANTA IS DEAD LEFT
	deadLeft.PushBack({ 2431 / 2,57 / 2,270 / 2,156 / 2 });
	deadLeft.PushBack({ 2162 / 2,57 / 2,270 / 2,156 / 2 });
	deadLeft.PushBack({ 1891 / 2,57 / 2,270 / 2,156 / 2 });
	deadLeft.PushBack({ 1621 / 2,57 / 2,270 / 2,156 / 2 });
	deadLeft.PushBack({ 1351 / 2,57 / 2,270 / 2,156 / 2 });
	deadLeft.PushBack({ 2431 / 2,327 / 2,270 / 2,156 / 2 });
	deadLeft.PushBack({ 2162 / 2,327 / 2,270 / 2,156 / 2 });
	deadLeft.PushBack({ 1891 / 2,327 / 2,270 / 2,156 / 2 });
	deadLeft.PushBack({ 1621 / 2,327 / 2,270 / 2,156 / 2 });

	deadLeft.speed = 0.2f;
	deadLeft.loop = false;

	//ANIMATION WHEN SANTA IS RUNNING LEFT
	runLeft.PushBack({ 2431 / 2,1407 / 2,260 / 2,156 / 2 });
	runLeft.PushBack({ 2162 / 2,1407 / 2,260 / 2,156 / 2 });
	runLeft.PushBack({ 1891 / 2,1407 / 2,260 / 2,156 / 2 });
	runLeft.PushBack({ 1621 / 2,1407 / 2,260 / 2,156 / 2 });
	runLeft.PushBack({ 1351 / 2,1407 / 2,260 / 2,156 / 2 });
	
	runLeft.speed = 0.2f;
	runLeft.loop = true;
	name.Create("player");
}

bool Player::Start()
{
	noise = true;
	cont = 0;
	app->SaveGameRequest("save_game.xml");
	result = collisionPosition::null;
	intro = true;
	godMode = false;
	lifes = 3;
	points = 0;

	//LOAD TEXTURES
	santa = app->tex->Load("Assets/textures/santa_animation.png");
	winTex = app->tex->Load("Assets/textures/win_screen.png");
	deadTex = app->tex->Load("Assets/textures/dead_screen.png");
	introTex = app->tex->Load("Assets/textures/title_screen.png");
	jumpFx = app->audio->LoadFx("Assets/audio/fx/santa_jump.ogg");
	landFx = app->audio->LoadFx("Assets/audio/fx/santa_land.wav");
	coinFx = app->audio->LoadFx("Assets/audio/fx/coin_drop.wav");
	lifeFx = app->audio->LoadFx("Assets/audio/fx/life.wav");
	checkpointFx = app->audio->LoadFx("Assets/audio/fx/checkpoint.wav");
	lifesTex = app->tex->Load("Assets/textures/lifes.png");
	currentAnimation = &stopRight;

	//INITIALIZE VARIABLES
	isJumping = false;
	canMove = true;
	win = false;
	dead = false;

	acceleration = 13.0f;
	velocity = 0;

	SDL_Rect rect = { position.x, position.y, 38, 5 };
	playerDown = app->collisions->AddCollider(rect, Collider::PLAYER, (Module*)this);
	rect = { position.x, position.y, 5, 74 };
	playerRight = app->collisions->AddCollider(rect, Collider::PLAYERRIGHT, (Module*)this);
	rect = { position.x, position.y, 5, 74 };
	playerLeft = app->collisions->AddCollider(rect, Collider::PLAYERLEFT, (Module*)this);
	lateralsR = false;
	lateralsL = false;
	lastPosition = position;
	return true;
}

bool Player::Update(float dt)
{
	if (position.x>=2610 && position.x <= 2620)
	{
		noise = true;
	}
	playerDown->SetPos(position.x + app->render->camera.x + 48, position.y + app->render->camera.y + 73);
	playerRight->SetPos(position.x + app->render->camera.x + 90, position.y + app->render->camera.y + 0);
	playerLeft->SetPos(position.x + app->render->camera.x + 40, position.y + app->render->camera.y + 0);

	//INPUT TO MOVE THE PLAYER
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && canMove == true)
	{
		if (lateralsR == false) 
		{
	
			if ((state == playerState::null) && (godMode == false))
			{
				lastanimation = currentAnimation;
				currentAnimation = &runRight;
				currentAnimation->Update();
			}
			if (state == playerState::jumping) 
			{
				currentAnimation = &jumpRight;
			}
			lastPosition = position;
		    position.x += 300* (dt / 1000);
		}
	}

	else if ((app->input->GetKey(SDL_SCANCODE_A)) == (KEY_REPEAT) && (canMove == true))
	{
		if (lateralsL == false) 
		{
			if (state==playerState::null)
			{
				lastanimation = currentAnimation;
				currentAnimation = &runLeft;
				currentAnimation->Update();
			}
			if ((state) == (playerState::jumping))
			{
				currentAnimation = &jumpLeft;
			}
			lastPosition = position;
			position.x -= 300 * (dt / 1000);
		}
	}

	if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) && (canMove == true))
	{
		if(godMode == true)
		{
			position.y -= 300 * (dt / 1000);
		}
	}

	else if ((app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (canMove == true))
	{
		if (godMode == true) 
		{
			position.y += 300 * (dt/1000);
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && canMove == true)
	{
		if (state==playerState::null) 
		{
			if (currentAnimation == &runRight || currentAnimation == &stopRight )
			{
				lastanimation = currentAnimation;
				currentAnimation = &jumpRight;
			}
			else if (currentAnimation == &runLeft || currentAnimation == &stopLeft)
			{
				lastanimation = currentAnimation;
				currentAnimation = &jumpLeft;

			}
			state = playerState::jumping;
			currentAnimation->Update();
		}
		
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

	if (lifes <= 0)
	{
		currentAnimation == &deadRight;
	}

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) 
	{
		app->SaveGameRequest("save_game.xml");
	}

	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{
		app->LoadGameRequest("save_game.xml");
	}

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN || ((app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)) && currentLevel == 1)
	{
		app->fade->FadeToBlack(this, (Module*)app->scene, 60);
	}

	if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN || ((app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)) && currentLevel == 2)
	{
		app->fade->FadeToBlack(this, (Module*)app->scene2, 60);
	}

	//JUST UPDATE THE ANIMATION
	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_UP)
	{
		lastanimation = currentAnimation;
		currentAnimation = &stopRight;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_UP)
	{
		lastanimation = currentAnimation;
		currentAnimation = &stopLeft;
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
		if (godMode == false) 
		{
			Gravity(dt);
		}
	}

	if ((currentAnimation == &deadRight || currentAnimation == &deadLeft) && currentAnimation->HasFinished() == true)
	{
		dead = false;
		app->fade->FadeToBlack(this, (Module*)app->dead, 50);
	}
	currentAnimation->Update();

	return true;
}

bool Player::PostUpdate() 
{
	SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(santa, position.x, position.y, &rect);

	switch (lifes)
	{
	case 5:
		rect = { 0,0,270,58 };
		app->render->DrawTexture(lifesTex, app->render->camera.x * -1, app->render->camera.y * -1, &rect);
		break;
	case 4:
		rect = { 0,0,216,58 };
		app->render->DrawTexture(lifesTex, app->render->camera.x * -1, app->render->camera.y * -1, &rect);
		break;
	case 3:
		rect = { 0,0,162,58 };
		app->render->DrawTexture(lifesTex,app->render->camera.x*-1, app->render->camera.y*-1, &rect);
		break;
	case 2:
		rect = { 0,0,108,58 };
		app->render->DrawTexture(lifesTex, app->render->camera.x*-1, app->render->camera.y*-1, &rect);
		break;
	case 1:
		rect = { 0,0,54,58 };
		app->render->DrawTexture(lifesTex, app->render->camera.x*-1, app->render->camera.y*-1, &rect);
		break;
	default:
		break;
	}

	if (dead == true)
	{
		if (lifes != 0)
		{
			dead = false;
			app->LoadGameRequest("save_game.xml");
		}

		if (lifes <= 0)
		{
			if (currentAnimation == &runRight || currentAnimation == &stopRight || currentAnimation == &jumpRight)
			{
				currentAnimation = &deadRight;
			}
			else if (currentAnimation == &runLeft || currentAnimation == &stopLeft || currentAnimation == &jumpLeft)
			{
				currentAnimation = &deadLeft;
			}
			canMove = false;
		}
	}
	
	if (win == true)
	{
		app->fade->FadeToBlack(this, (Module*)app->winp, 50);
		win = false;
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
	app->tex->UnLoad(winTex);
	app->tex->UnLoad(deadTex);
	app->tex->UnLoad(santa);
	app->tex->UnLoad(introTex);
	app->scene->Disable();
	app->scene2->Disable();
	return true;
}

void Player::Gravity(float dt)
{
	lastPosition = position;
	velocity += acceleration * 0.05 * 100 * (dt / 1000);
	position.y += velocity * 0.05 * 100 * (dt / 1000);
	app->render->camera.y -= velocity * 0.05 * 100 * (dt/1000);
}

//PLAYER FUNCTIONS
void Player::JumpFunction(float dt)
{
	collisionPosition result;
	if (jumpingCount < 30)
	{
		if (((lastanimation == &runLeft) || (lastanimation == &stopLeft)))
		{
			lastanimation = currentAnimation;
			currentAnimation = &jumpLeft;
		}
		if (((lastanimation == &runRight) || (lastanimation == &stopRight)))
		{
			lastanimation = currentAnimation;
			currentAnimation = &jumpRight;
		}
		lastPosition = position;
		position.y -= 200*(dt/1000);
		app->render->camera.y += 150*(dt/1000);
		jumpingCount+= (dt/15);
		
	}
	else 
	{
		lastPosition = position;
		state = playerState::free;
		jumpingCount = 0;
		position.y += 3;
		velocity = 5.0f;
	}
}

void Player::DeadAction()
{
	if ((currentAnimation == &runRight) || (currentAnimation == &stopRight) || (currentAnimation == &jumpRight))
	{
		lastanimation = currentAnimation;
		currentAnimation = &deadRight;
		currentAnimation->Update();
	}
	else if ((currentAnimation == &runLeft) || (currentAnimation == &stopLeft) || (currentAnimation == &jumpLeft))
	{
		lastanimation = currentAnimation;
		currentAnimation = &deadLeft;
		currentAnimation->Update();
	}
}

bool Player::SaveState(pugi::xml_node* nodo)
{
	pugi::xml_node node=nodo->append_child("data");
	node.append_attribute("x").set_value(position.x);
	node.append_attribute("y").set_value(position.y);
	node.append_attribute("aceleration") = acceleration;
	
	return true;
}

bool Player::LoadState(pugi::xml_node* nodo)
{
	position.x = nodo->child("data").attribute("x").as_int();
	position.y = nodo->child("data").attribute("y").as_int();
	acceleration = nodo->child("data").attribute("aceleration").as_int();
	return true;
}

void Player::OnCollision(Collider* c1, Collider* c2) 
{
	if (godMode == false)
	{
		if (c1->type == Collider::PLAYER)
		{
			if (c2->type == Collider::FLOOR)
			{
				if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
				{
					app->audio->PlayFx(jumpFx);
				}
				state = playerState::null;
				int sum = 0;
				while (true) 
				{
					if (c1->Intersects(c2->rect) == true) 
					{
						sum -= 1;
						c1->rect.y -= 1;
						if (c1->Intersects(c2->rect) == false) {
							c1->rect.y += 1;
							sum += 1;
							break;
						}
					}
				}
				position.y += sum;
				velocity = 0;
			}
			else if (c2->type == Collider::COIN)
			{
				points += 100;
				app->audio->PlayFx(coinFx);
				c2->pendingToDelete = true;
			}
			else if (c2->type == Collider::HEART)
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
					lateralsR = true;
				}
				else
				{
					lateralsR = true;
				}
			}
			else if (c2->type == Collider::CHECKPOINT)
			{
				app->SaveGameRequest("save_game.xml");
				if (noise == true)
				{
					app->audio->PlayFx(app->player->checkpointFx);
					noise = false;
				}
			}
			else if (c2->type == Collider::WALL)
			{
				state = playerState::free;
				lateralsR = true;
			}
			else if (c2->type == Collider::ENEMY2)
			{
				ListItem<Entity*>* aux = app->entity->entityList.start;
				while (aux != nullptr)
				{
					if (aux->data->collider == c2)
					{
						if (aux->data->deadZ == true && dead==false) {}
						else
						{
							dead = true;
							lifes--;;
						}
					}
					aux = aux->next;
				}
			}
			else if (c2->type == Collider::COIN)
			{
				points += 100;
				app->audio->PlayFx(coinFx);
				c2->pendingToDelete = true;
			}
			else if (c2->type == Collider::HEART)
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
					lateralsL = true;
				}
				else
				{

					lateralsL = true;
				}
			}
			else if (c2->type == Collider::WALL)
			{
				state = playerState::free;
				lateralsL = true;
			}
			else if (c2->type == Collider::ENEMY2)
			{
				ListItem<Entity*>* aux = app->entity->entityList.start;
				while (aux != nullptr)
				{
					if (aux->data->collider == c2)
					{
						if (aux->data->deadZ == true) {}
						else
						{
							dead = true;
							lifes--;
						}
					}
					aux = aux->next;
				}
			}
			else if (c2->type == Collider::COIN)
			{
				points += 100;
				app->audio->PlayFx(coinFx);
				c2->pendingToDelete = true;
			}
			else if (c2->type == Collider::HEART)
			{
				points += 50;
				app->audio->PlayFx(lifeFx);
				lifes++;
				c2->pendingToDelete = true;
			}
		}
	}
}

bool Player::HasThePlayerMove() 
{
	iPoint actual, previous;
	actual=app->map->WorldToMap(position.x, position.y);
	previous = app->map->WorldToMap(lastPosition.x, lastPosition.y);
	if (actual != previous) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

iPoint Player:: GetPosition()
{
	iPoint point;
	point.x = position.x;
	point.y = position.y;
	return point;
}
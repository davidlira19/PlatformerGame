#include "Enemy_Ground.h"
#include "App.h"
#include "EntityManager.h"
#include "Collisions.h"
#include "Player.h"
#include "Audio.h"

EnemyGround::EnemyGround(int x, int y) : Entity(x, y)
{
	zombieMoveLeft.PushBack({ 0,156,52,77 });
	zombieMoveLeft.PushBack({ 111,156,52,77 });
	zombieMoveLeft.PushBack({ 222,156,52,77 });
	zombieMoveLeft.PushBack({ 333,156,52,77 });
	zombieMoveLeft.PushBack({ 444,156,52,77 });
	zombieMoveLeft.PushBack({ 555,156,52,77 });
	zombieMoveLeft.PushBack({ 666,156,52,77 });
	zombieMoveLeft.PushBack({ 777,156,52,77 });
	zombieMoveLeft.PushBack({ 888,156,52,77 });
	zombieMoveLeft.PushBack({ 999,156,52,77 });
	zombieMoveLeft.loop = true;
	zombieMoveLeft.speed = 0.15f;

	zombieMoveRight.PushBack({ 1058,390,52,77 });
	zombieMoveRight.PushBack({ 947,390,52,77 });
	zombieMoveRight.PushBack({ 836,390,52,77 });
	zombieMoveRight.PushBack({ 725,390,52,77 });
	zombieMoveRight.PushBack({ 614,390,52,77 });
	zombieMoveRight.PushBack({ 503,390,52,77 });
	zombieMoveRight.PushBack({ 392,390,52,77 });
	zombieMoveRight.PushBack({ 281,390,52,77 });
	zombieMoveRight.PushBack({ 170,390,52,77 });
	zombieMoveRight.PushBack({ 59,390,110,77 });
	zombieMoveRight.loop = true;
	zombieMoveRight.speed = 0.15f;

	zombieDeadLeft.PushBack({ 0,0,110,77 });
	zombieDeadLeft.PushBack({ 111,0,110,77 });
	zombieDeadLeft.PushBack({ 222,0,110,77 });
	zombieDeadLeft.PushBack({ 333,0,110,77 });
	zombieDeadLeft.PushBack({ 444,0,110,77 });
	zombieDeadLeft.PushBack({ 555,0,110,77 });
	zombieDeadLeft.PushBack({ 666,0,110,77 });
	zombieDeadLeft.PushBack({ 777,0,110,77 });
	zombieDeadLeft.loop = false;
	zombieDeadLeft.speed = 0.15f;

	zombieDeadRight.PushBack({ 999,234,110,77 });
	zombieDeadRight.PushBack({ 888,234,110,77 });
	zombieDeadRight.PushBack({ 777,234,110,77 });
	zombieDeadRight.PushBack({ 666,234,110,77 });
	zombieDeadRight.PushBack({ 555,234,110,77 });
	zombieDeadRight.PushBack({ 444,234,110,77 });
	zombieDeadRight.PushBack({ 333,234,110,77 });
	zombieDeadRight.PushBack({ 222,234,110,77 });
	zombieDeadRight.loop = false;
	zombieDeadRight.speed = 0.15f;

	currentAnim = &zombieMoveLeft;

	left = true;
	deadZ = false;

	playerWin = app->collisions->AddCollider({ 0, 0, 48, 4 }, Collider::ENEMY1, (Module*)app->entity);
	collider = app->collisions->AddCollider({ 0, 6, 48, 77 }, Collider::ENEMY2, (Module*)app->entity);

	zombieFx = app->audio->LoadFx("Assets/audio/fx/zombie_pain.wav");
}

EnemyGround::~EnemyGround()
{
	collider->pendingToDelete = true;
	playerWin->pendingToDelete = true;
}

void EnemyGround::Update()
{
	playerWin->SetPos(position.x + app->render->camera.x, position.y + app->render->camera.y - 20);
	collider->SetPos(position.x + app->render->camera.x, position.y + app->render->camera.y + 6 - 20);

	if (dire == -1)
	{
		if (deadZ == false)
		{
			currentAnim = &zombieMoveLeft;
		}
		else
		{
			currentAnim = &zombieDeadLeft;
		}
	}
	else
	{
		if (deadZ == false)
		{
			currentAnim = &zombieMoveRight;
		}
		else
		{
			currentAnim = &zombieDeadRight;
		}
	}

	if ((currentAnim == &zombieDeadLeft || currentAnim == &zombieDeadRight) && currentAnim->HasFinished() == true)
	{
		pendientedeelim = true;
		cont = 0;
	}

	currentAnim->Update();

	Entity::Update();
}

void EnemyGround::Draw()
{
	SDL_Rect rect = currentAnim->GetCurrentFrame();

	if (&zombieDeadLeft == currentAnim|| &zombieDeadRight == currentAnim)
	{
		app->render->DrawTexture(groundEnemiesTexture, position.x, position.y-20, &rect);
	}
	else 
	{
		app->render->DrawTexture(groundEnemiesTexture, position.x, position.y-20, &rect);
	}

	if (app->entity->drawItems == true)
	{
		SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(app->render->renderer, 0, 255, 255, 80);
		SDL_RenderFillRect(app->render->renderer, &playerWin->rect);
		SDL_SetRenderDrawColor(app->render->renderer, 0, 255, 255, 80);
		SDL_RenderFillRect(app->render->renderer, &collider->rect);
	}
}

void EnemyGround::OnCollision(Collider* collideri, Collider* collidere)
{
	if (collideri->type == Collider::ENEMY1)
	{
		if (collidere->type == Collider::PLAYER)
		{
			if (type == EntityTipe::EnemyGround)
			{
				deadZ = true;
				if (cont == 0)
				{
					app->audio->PlayFx(zombieFx);
					app->player->points += 200;
				}
				cont = 1;
			}
		}
	}
}
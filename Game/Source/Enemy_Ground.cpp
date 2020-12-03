#include "Enemy_Ground.h"

#include "App.h"
#include "EntityManager.h"
#include "Collisions.h"
#include "Player.h"


EnemyGround::EnemyGround(int x, int y) : Entity(x, y)
{
	zombieMoveLeft.PushBack({ 1,312 / 2,99 / 2,154 / 2 });
	zombieMoveLeft.PushBack({ 222 / 2,312 / 2,100 / 2,154 / 2 });
	zombieMoveLeft.PushBack({ 445 / 2,313 / 2,99 / 2,153 / 2 });
	zombieMoveLeft.PushBack({ 667 / 2,313 / 2,99 / 2,153 / 2 });
	zombieMoveLeft.PushBack({ 889 / 2,314 / 2,99 / 2,152 / 2 });
	zombieMoveLeft.PushBack({ 1110 / 2,313 / 2,98 / 2,153 / 2 });
	zombieMoveLeft.PushBack({ 1332 / 2,313 / 2,99 / 2,153 / 2 });
	zombieMoveLeft.PushBack({ 1554 / 2,312 / 2,100 / 2,154 / 2 });
	zombieMoveLeft.PushBack({ 1776 / 2,311 / 2,100 / 2,155 / 2 });
	zombieMoveLeft.PushBack({ 1998 / 2,311 / 2,99 / 2,155 / 2 });
	zombieMoveLeft.loop = true;
	zombieMoveLeft.speed = 0.15f;

	zombieMoveRight.PushBack({ 59,387,50,77 });
	zombieMoveRight.PushBack({ 170,387,50,77 });
	zombieMoveRight.PushBack({ 280,387,50,77 });
	zombieMoveRight.PushBack({ 392,387,50,77 });
	zombieMoveRight.PushBack({ 504,387,50,77 });
	zombieMoveRight.PushBack({ 614,387,50,77 });
	zombieMoveRight.PushBack({ 726,387,50,77 });
	zombieMoveRight.PushBack({ 837,387,50,77 });
	zombieMoveRight.PushBack({ 948,387,50,77 });
	zombieMoveRight.PushBack({ 1059,387,50,77 });
	zombieMoveRight.loop = true;
	zombieMoveRight.speed = 0.15f;

	zombieDeadLeft.PushBack({ 17,2,58,72 });
	zombieDeadLeft.PushBack({ 125,9,69,66 });
	zombieDeadLeft.PushBack({ 239,19,71,55 });
	zombieDeadLeft.PushBack({ 353,36,69,38 });
	zombieDeadLeft.PushBack({ 464,38,75,36 });
	zombieDeadLeft.PushBack({ 575,48,78,26 });
	zombieDeadLeft.PushBack({ 679,61,96,13 });
	zombieDeadLeft.PushBack({ 776,68,113,6 });
	zombieDeadLeft.loop = false;
	zombieDeadLeft.speed = 0.15f;

	zombieDeadRight.PushBack({ 1034,236,58,72 });
	zombieDeadRight.PushBack({ 915,243,69,66 });
	zombieDeadRight.PushBack({ 799,254,71,55 });
	zombieDeadRight.PushBack({ 687,271,69,38 });
	zombieDeadRight.PushBack({ 570,273,75,36 });
	zombieDeadRight.PushBack({ 455,283,78,26 });
	zombieDeadRight.PushBack({ 334,296,96,13 });
	zombieDeadRight.PushBack({ 220,303,113,6 });
	zombieDeadRight.loop = false;
	zombieDeadRight.speed = 0.15f;
	//////
	currentAnim = &zombieMoveLeft;

	left = true;
	deadZ = false;

	playerWin = app->collisions->AddCollider({ 0, 0, 48, 4 }, Collider::ENEMY1, (Module*)app->entity);
	collider = app->collisions->AddCollider({ 0, 6, 48, 77 }, Collider::ENEMY2, (Module*)app->entity);


}
EnemyGround::~EnemyGround()
{
	collider->pendingToDelete = true;
	playerWin->pendingToDelete = true;
}
void EnemyGround::Update()
{
	playerWin->SetPos(position.x + app->render->camera.x, position.y + app->render->camera.y);
	collider->SetPos(position.x + app->render->camera.x, position.y + app->render->camera.y + 6);

	if (left == true)
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

	currentAnim->Update();

	Entity::Update();
}
void EnemyGround::Draw()
{

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->render->DrawTexture(groundEnemiesTexture, position.x, position.y, &rect);

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
				app->player->points += 200;
			}
			pendientedeelim = true;
		}

	}
}
#include "Enemy_Ground.h"

#include "App.h"
#include "Collisions.h"


EnemyGround::EnemyGround(int x, int y) : Entity(x, y)
{
	zombieMoveLeft.PushBack({ 1,312/2,99 / 2,154 / 2 });
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
	//////
	currentAnim = &zombieMoveLeft;
	playerWin = app->collisions->AddCollider({ 0, 0, 48, 4 }, Collider::ENEMY1, (Module*)app->enemy);
	collider = app->collisions->AddCollider({ 0, 6, 48, 77 }, Collider::ENEMY2, (Module*)app->enemy);
	

}

void EnemyGround::Update()
{
	playerWin->SetPos(position.x + app->render->camera.x, position.y + app->render->camera.y);
	collider->SetPos(position.x + app->render->camera.x, position.y + app->render->camera.y+6);
	
	currentAnim->Update();

	Entity::Update();
}
void EnemyGround::Draw()
{

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->render->DrawTexture(groundEnemiesTexture, position.x, position.y, &rect);


	SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app->render->renderer, 0, 255, 255, 80);
	SDL_RenderFillRect(app->render->renderer, &playerWin->rect);
	SDL_SetRenderDrawColor(app->render->renderer, 0, 255, 255, 80);
	SDL_RenderFillRect(app->render->renderer, &collider->rect);
}
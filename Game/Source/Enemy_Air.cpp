#include "Enemy_Air.h"
#include "EntityManager.h"
#include "App.h"
#include "Collisions.h"

EnemyAir::EnemyAir(int x, int y) : Entity(x, y)
{
	birdAnim.PushBack({ 0,0,88,58 });
	birdAnim.PushBack({ 90,0,88,58 });
	birdAnim.PushBack({ 181,0,88,58 });
	birdAnim.PushBack({ 272,0,88,58 });
	birdAnim.loop = true;
	birdAnim.speed = 0.1f;
	currentAnim = &birdAnim;
	playerWin = app->collisions->AddCollider({ 0, 0, 88, 4 }, Collider::ENEMY1, (Module*)app->entity);
	collider = app->collisions->AddCollider({ 0, 6, 88, 56 }, Collider::ENEMY2, (Module*)app->entity);

}

EnemyAir::~EnemyAir() 
{
	collider->pendingToDelete = true;
	playerWin->pendingToDelete = true;
}

void EnemyAir::Update()
{
	playerWin->SetPos(position.x + app->render->camera.x, position.y + app->render->camera.y-40);
	collider->SetPos(position.x + app->render->camera.x, position.y + app->render->camera.y-34);
	
	currentAnim->Update();

	Entity::Update();
}

void EnemyAir::Draw()
{
	SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->render->DrawTexture(airEnemiesTexture, position.x, position.y-40, &rect);

	if (app->entity->drawItems == true)
	{
		SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(app->render->renderer, 0, 255, 255, 80);
		SDL_RenderFillRect(app->render->renderer, &playerWin->rect);
		SDL_SetRenderDrawColor(app->render->renderer, 0, 255, 255, 80);
		SDL_RenderFillRect(app->render->renderer, &collider->rect);
	}
}
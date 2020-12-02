#include "Coin.h"

#include "App.h"
#include "EntityManager.h"
#include "Collisions.h"


Coin::Coin(int x, int y) : Entity(x, y)
{
	coinAnim.PushBack({ 4 / 2,3 / 2,85 / 2,85 / 2 });
	coinAnim.PushBack({ 94 / 2,3 / 2,85 / 2,85 / 2 });
	coinAnim.PushBack({ 184 / 2,3 / 2,85 / 2,85 / 2 });
	coinAnim.PushBack({ 4 / 2,93 / 2,85 / 2,85 / 2 });
	coinAnim.PushBack({ 94 / 2,93 / 2,85 / 2,85 / 2 });
	coinAnim.PushBack({ 184 / 2,93 / 2,85 / 2,85 / 2 });
	coinAnim.loop = true;
	coinAnim.speed = 0.15f;
	//////
	currentAnim = &coinAnim;
	collider = app->collisions->AddCollider({ 0, 0, 42, 42 }, Collider::COIN, (Module*)app->entity);
	

}
Coin::~Coin()
{
	collider->pendingToDelete = true;
}
void Coin::Update()
{
	collider->SetPos(position.x + app->render->camera.x, position.y + app->render->camera.y+6);
	
	currentAnim->Update();

	Entity::Update();
}
void Coin::Draw()
{

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->render->DrawTexture(moneyTexture, position.x, position.y, &rect);

	if (app->entity->drawItems == true)
	{
		SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(app->render->renderer, 0, 255, 255, 80);
		SDL_RenderFillRect(app->render->renderer, &collider->rect);
	}

}
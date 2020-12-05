#include "Heart.h"
#include "App.h"
#include "EntityManager.h"
#include "Collisions.h"

Heart::Heart(int x, int y) : Entity(x, y)
{
	heartAnim.PushBack({ 2,2,62,62 });
	heartAnim.PushBack({ 67,2,62,62 });
	heartAnim.PushBack({ 132,2,62,62 });
	heartAnim.PushBack({ 2,67,62,62 });
	heartAnim.PushBack({ 67,67,62,62 });
	heartAnim.PushBack({ 132,67,62,62 });
	heartAnim.loop = true;
	heartAnim.speed = 0.15f;

	currentAnim = &heartAnim;

	collider = app->collisions->AddCollider({ 0, 0, 42, 42 }, Collider::HEART, (Module*)app->entity);
}

Heart::~Heart()
{
	collider->pendingToDelete = true;
}

void Heart::Update(float dt)
{
	collider->SetPos(position.x + app->render->camera.x, position.y + app->render->camera.y + 6);

	currentAnim->Update();

	Entity::Update(dt);
}

void Heart::Draw()
{
	SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->render->DrawTexture(lifeTexture, position.x, position.y, &rect);

	if (app->entity->drawItems == true)
	{
		SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(app->render->renderer, 0, 255, 255, 80);
		SDL_RenderFillRect(app->render->renderer, &collider->rect);
	}
}
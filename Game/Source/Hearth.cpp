#include "Hearth.h"

#include "App.h"
#include "EntityManager.h"
#include "Collisions.h"


Hearth::Hearth(int x, int y) : Entity(x, y)
{
	hearthAnim.PushBack({ 1,1,62,62 });
	hearthAnim.PushBack({ 66,1,62,62 });
	hearthAnim.PushBack({ 131,1,62,62 });
	hearthAnim.PushBack({ 1,66,62,62 });
	hearthAnim.PushBack({ 66,66,62,62 });
	hearthAnim.PushBack({ 131,66,62,62 });
	hearthAnim.loop = true;
	hearthAnim.speed = 0.15f;
	//////
	currentAnim = &hearthAnim;
	collider = app->collisions->AddCollider({ 0, 0, 42, 42 }, Collider::HEARTH, (Module*)app->entity);


}
Hearth::~Hearth()
{
	collider->pendingToDelete = true;
}
void Hearth::Update()
{
	collider->SetPos(position.x + app->render->camera.x, position.y + app->render->camera.y + 6);

	currentAnim->Update();

	Entity::Update();
}
void Hearth::Draw()
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
#include "Entity.h"
#include"Textures.h"
#include "App.h"
//#include "Collisions.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "Render.h"

Entity::Entity(int x, int y) : position(x, y)
{

}

Entity::~Entity()
{
	/*
	if (collider != nullptr) {
		collider->pendingToDelete = true;
	}
	if (collider1 != nullptr) {
		collider1->pendingToDelete = true;
	}
	*/
}

/*const Collider* Enem::GetCollider() const
{
	return collider;
}*/
void Entity::Update()
{

}

void Entity::Draw()
{

	SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->render->DrawTexture(airEnemiesTexture, position.x, position.y,&rect);
}

void Entity::OnCollision(Collider* collideri, Collider* collidere)
{

}

void Entity::destr()
{
	/*
	if (collider != nullptr) {
		collider->pendingToDelete = true;
	}
	if (collider1 != nullptr) {
		collider1->pendingToDelete = true;

	}
	pendientedeelim = true;
	*/
}

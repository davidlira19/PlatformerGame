#include "Entity.h"
#include"Textures.h"
#include "App.h"
//#include "Collisions.h"
//#include "ModuleParticles.h"
#include "Player.h"
#include "EntityManager.h"
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

	/*SDL_Rect rect = currentAnim->GetCurrentFrame();
	app->render->DrawTexture(airEnemiesTexture, position.x, position.y,&rect);
	app->render->DrawTexture(groundEnemiesTexture, position.x, position.y, &rect);*/
}

void Entity::OnCollision(Collider* collideri, Collider* collidere)
{
	if (collideri->type == Collider::ENEMY1) 
	{
		if (collidere->type == Collider::PLAYER) 
		{
			if (type == EntityTipe::EnemyAir)
			{
				app->player->points += 300;
			}
			if (type == EntityTipe::EnemyGround)
			{
				app->player->points += 200;
			}
			pendientedeelim = true;
		}
		
	}
	if (collidere->type == Collider::PLAYER || collidere->type == Collider::PLAYERLEFT || collidere->type == Collider::PLAYERRIGHT)
	{
		if (collideri->type == Collider::COIN ||collideri->type == Collider::HEARTH)
		{
			pendientedeelim = true;
		}

	}
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

#include "Enemy_Ground.h"

#include "App.h"
//#include "Collisions.h"


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
	//collider = app->collisions->AddCollider({ 0, 0, 25, 11 }, Collider::Type::Enemigo, (Module*)App->enemies);
	//collider1 = app->collisions->AddCollider({ 0, 0, 5, 5 }, Collider::Type::top, (Module*)App->enemies);

}

void EnemyGround::Update()
{
	currentAnim->Update();

	Entity::Update();
}
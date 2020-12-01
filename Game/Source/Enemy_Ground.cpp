#include "Enemy_Ground.h"

#include "App.h"
//#include "Collisions.h"


EnemyGround::EnemyGround(int x, int y) : Entity(x, y)
{
	zombieMoveLeft.PushBack({ 1,312,99,154 });
	zombieMoveLeft.PushBack({ 222,312,100,154 });
	zombieMoveLeft.PushBack({ 445,313,99,153 });
	zombieMoveLeft.PushBack({ 667,313,99,123 });
	zombieMoveLeft.PushBack({ 889,314,99,122 });
	zombieMoveLeft.PushBack({ 1110,313,98,123 });
	zombieMoveLeft.PushBack({ 1332,313,99,123 });
	zombieMoveLeft.PushBack({ 1554,312,100,124 });
	zombieMoveLeft.PushBack({ 1776,311,100,125 });
	zombieMoveLeft.PushBack({ 1998,311,99,125 });
	zombieMoveLeft.loop = true;
	zombieMoveLeft.speed = 0.1f;
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
#include "Enemy_Ground.h"

#include "App.h"
//#include "Collisions.h"


EnemyGround::EnemyGround(int x, int y) : Entity(x, y)
{
	GroundEnemAnim.PushBack({ 0,50,12,12 });
	GroundEnemAnim.PushBack({ 16,50,13,12 });
	GroundEnemAnim.PushBack({ 33,50,13,12 });
	GroundEnemAnim.PushBack({ 50,50,13,12 });
	GroundEnemAnim.loop = true;
	GroundEnemAnim.speed = 0.1f;
	//////
	currentAnim = &GroundEnemAnim;
	//collider = app->collisions->AddCollider({ 0, 0, 25, 11 }, Collider::Type::Enemigo, (Module*)App->enemies);
	//collider1 = app->collisions->AddCollider({ 0, 0, 5, 5 }, Collider::Type::top, (Module*)App->enemies);

}

void EnemyGround::Update()
{


	Entity::Update();
}
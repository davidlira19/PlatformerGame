#include "Enemy_Air.h"

#include"Enemies.h"
#include "App.h"
//#include "Collisions.h"


EnemyAir::EnemyAir(int x, int y) : Entity(x, y)
{
	AirEnemAnim.PushBack({ 0,0,88,58 });
	AirEnemAnim.PushBack({ 90,5,72,58 });
	AirEnemAnim.PushBack({ 33,14,13,12 });
	AirEnemAnim.PushBack({ 50,14,13,12 });
	AirEnemAnim.loop = true;
	AirEnemAnim.speed = 0.1f;
	currentAnim = &AirEnemAnim;
	//collider = app->collisions->AddCollider({ 0, 0, 25, 11 }, Collider::Type::Enemigo, (Module*)App->enemies);
	//collider1 = app->collisions->AddCollider({ 0, 0, 5, 5 }, Collider::Type::top, (Module*)App->enemies);

}
EnemyAir::~EnemyAir() {

}
void EnemyAir::Update()
{


	Entity::Update();
}

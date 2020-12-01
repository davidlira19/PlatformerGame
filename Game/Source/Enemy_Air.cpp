#include "Enemy_Air.h"

#include"EntityManager.h"
#include "App.h"
//#include "Collisions.h"


EnemyAir::EnemyAir(int x, int y) : Entity(x, y)
{
	birdAnim.PushBack({ 0,0,88,58 });
	birdAnim.PushBack({ 90,0,88,58 });
	birdAnim.PushBack({ 181,0,88,58 });
	birdAnim.PushBack({ 272,0,88,58 });
	birdAnim.loop = true;
	birdAnim.speed = 0.1f;
	currentAnim = &birdAnim;
	//collider = app->collisions->AddCollider({ 0, 0, 25, 11 }, Collider::Type::Enemigo, (Module*)App->enemies);
	//collider1 = app->collisions->AddCollider({ 0, 0, 5, 5 }, Collider::Type::top, (Module*)App->enemies);

}
EnemyAir::~EnemyAir() {

}
void EnemyAir::Update()
{
	currentAnim->Update();

	Entity::Update();
}

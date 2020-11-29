#include "Enemy_Air.h"

#include"Enemies.h"
#include "App.h"
//#include "Collisions.h"


EnemyAir::EnemyAir(int x, int y, int direccion) : Enem(x, y)
{
	AirEnemAnim.PushBack({ 0,14,12,12 });
	AirEnemAnim.PushBack({ 16,14,13,12 });
	AirEnemAnim.PushBack({ 33,14,13,12 });
	AirEnemAnim.PushBack({ 50,14,13,12 });
	AirEnemAnim.loop = true;
	AirEnemAnim.speed = 0.1f;
	frames1 = 0;
	top1 = true;

	dire = direccion;
	/////
	typo = tipo::Air;
	estado = state::recto;
	contsub = 0;
	//////
	currentAnim = &AirEnemAnim;
	//collider = app->collisions->AddCollider({ 0, 0, 25, 11 }, Collider::Type::Enemigo, (Module*)App->enemies);
	//collider1 = app->collisions->AddCollider({ 0, 0, 5, 5 }, Collider::Type::top, (Module*)App->enemies);

}

void EnemyAir::Update()
{
	if (estado == state::recto) {
		position.x = (position.x + (2 * dire));
		if (currentAnim != &AirEnemAnim) {
			currentAnim = &AirEnemAnim;
		}

		estado = state::libre;

	}
	else if (estado == state::libre) {

		position.y = position.y + 3;
		//position.x = (position.x + (1 * dire));
		if (contsub == 5) {
			
			if (dire == 1) {
				dire = -1;
			}
			else {
				dire = 1;
			}
		}
		//frames1++;
		contsub++;
		//estado == state::recto;
	}
	else if (estado == state::bajando) {
		if (currentAnim != &AirEnemAnim) {
			currentAnim = &AirEnemAnim;
		}

		position.y = position.y + 2;
		if (top1 == true) {
			top1 = false;
		}
		else {

			top1 = true;
			estado = state::recto;
			if (dire == 1) {
				dire = -1;
			}
			else {
				dire = 1;
			}
		}

	}
	if (position.x < 67 && position.y>645) {
		Enem::destr();
		app->enemy->AddEnemy(Enemy_Type::Air, 80, 703, 1);

	}
	frames1++;

	Enem::Update();
}
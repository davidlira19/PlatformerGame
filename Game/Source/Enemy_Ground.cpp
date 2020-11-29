#include "Enemy_Ground.h"

#include "App.h"
//#include "Collisions.h"


EnemyGround::EnemyGround(int x, int y, int direccion) : Enem(x, y)
{
	GroundEnemAnim.PushBack({ 0,50,12,12 });
	GroundEnemAnim.PushBack({ 16,50,13,12 });
	GroundEnemAnim.PushBack({ 33,50,13,12 });
	GroundEnemAnim.PushBack({ 50,50,13,12 });
	GroundEnemAnim.loop = true;
	GroundEnemAnim.speed = 0.1f;
	frames1 = 0;
	frames2 = 0;
	top1 = true;

	dire = direccion;
	/////
	typo = tipo::Ground;
	estado = state::recto;
	contsub = 0;
	//////
	currentAnim = &GroundEnemAnim;
	//collider = app->collisions->AddCollider({ 0, 0, 25, 11 }, Collider::Type::Enemigo, (Module*)App->enemies);
	//collider1 = app->collisions->AddCollider({ 0, 0, 5, 5 }, Collider::Type::top, (Module*)App->enemies);

}

void EnemyGround::Update()
{
	if (estado == state::recto) {
		position.x = (position.x + (2 * dire));
		if (currentAnim != &GroundEnemAnim) {
			currentAnim = &GroundEnemAnim;
		}

		estado = state::libre;

	}
	else if (estado == state::libre) {

		position.y = position.y + 3;
		//position.x = (position.x + (1 * dire));
		if (contsub == 5) {
			estado = Enem::random(state::libre, collider, tipo::Ground);
			if (frames2 >= 4) {
				estado = state::saliendo;
			}
			if (estado == state::libre) {
				if (dire == 1) {
					dire = -1;
				}
				else {
					dire = 1;
				}
				frames2++;
			}

		}
		//frames1++;
		contsub++;
		//estado == state::recto;
	}
	else if (estado == state::bajando) {
		if (currentAnim != &GroundEnemAnim) {
			currentAnim = &GroundEnemAnim;
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
			frames2++;
		}

	}
	else if (estado == state::saliendo) {
		position.x = (position.x + (2 * dire));
		position.y = position.y + 2;
	}
	if (position.x < -5 || position.x > 672) {
		destr();
	}
	frames1++;

	Enem::Update();
}
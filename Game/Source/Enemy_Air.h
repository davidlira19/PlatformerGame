#ifndef __ENEMY_AIR_H__
#define __ENEMY_AIR_H__

#include "Enemy.h"
class EnemyAir : public Enem
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	EnemyAir(int x, int y, int direccion);
	// The enemy is going to perform a sinusoidal movement
	void Update();

private:
	// The position (as ratio) in the wave at a specific moment


	// The enemy animation
	Animation AirEnemAnim;
};

#endif

#ifndef __ENEMY_AIR_H__
#define __ENEMY_AIR_H__
#include"Animation.h"
#include "Entity.h"
class EnemyAir : public Entity
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	EnemyAir(int x, int y);
	~EnemyAir();
	// The enemy is going to perform a sinusoidal movement
	void Update();
	void Draw();
private:
	// The position (as ratio) in the wave at a specific moment

	
	// The enemy animation
	Animation birdAnim;
};

#endif

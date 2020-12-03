#ifndef __ENEMY_GROUND_H__
#define __ENEMY_GROUND_H__
#include"Animation.h"
#include "Entity.h"
class EnemyGround : public Entity
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	EnemyGround(int x, int y);
	~EnemyGround();
	// The enemy is going to perform a sinusoidal movement
	void Update();
	void Draw();
	void OnCollision(Collider* collideri, Collider* collidere);

	bool left;
	bool deadZ;

private:
	// The position (as ratio) in the wave at a specific moment

	// The enemy animation
	Animation zombieMoveLeft;
	Animation zombieMoveRight;
	Animation zombieDeadLeft;
	Animation zombieDeadRight;


};

#endif

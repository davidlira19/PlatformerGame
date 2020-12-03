#ifndef __HEART_H__
#define __HEART_H__
#include "Animation.h"
#include "Entity.h"
class Heart : public Entity
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Heart(int x, int y);
	~Heart();
	// The enemy is going to perform a sinusoidal movement
	void Update();
	void Draw();

private:
	// The position (as ratio) in the wave at a specific moment

	Collider* playerWin = nullptr;
	// The enemy animation
	Animation heartAnim;

};

#endif

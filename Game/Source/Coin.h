#ifndef __COIN_H__
#define __COIN_H__

#include "Animation.h"
#include "Entity.h"

class Coin : public Entity
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Coin(int x, int y);
	~Coin();

	// The enemy is going to perform a sinusoidal movement
	void Update(float dt);
	void Draw();

private:
	// The position (as ratio) in the wave at a specific moment

	Collider* playerWin = nullptr;

	// The enemy animation
	Animation coinAnim;
};

#endif
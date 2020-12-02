#ifndef __HEARTH_H__
#define __HEARTH_H__
#include "Animation.h"
#include "Entity.h"
class Hearth : public Entity
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Hearth(int x, int y);
	~Hearth();
	// The enemy is going to perform a sinusoidal movement
	void Update();
	void Draw();

private:
	// The position (as ratio) in the wave at a specific moment

	Collider* playerWin = nullptr;
	// The enemy animation
	Animation hearthAnim;

};

#endif

#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

class Module;

enum class collisionPosition
{
	down, right, left, downAndRight, downAndLeft, null
};

struct Collider
{
	enum Type
	{
		NONE = -1, PLAYER, PLAYERRIGHT, PLAYERLEFT, FLOOR, WALL, CHECKPOINT, ENEMY1, ENEMY2, COIN, HEART, MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);
	~Collider();
	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;
	
	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listener = nullptr;
};

#endif // !__COLLIDER_H__
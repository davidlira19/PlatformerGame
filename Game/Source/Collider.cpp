#include "Collider.h"
#include "App.h"
#include "Player.h"
Collider::Collider(SDL_Rect rectangle, Type type, Module* listener) : rect(rectangle), type(type), listener(listener)
{
	
}

void Collider::SetPos(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

bool Collider::Intersects(const SDL_Rect& r) const
{
	return (rect.x <= r.x + r.w &&
		rect.x + rect.w >= r.x &&
		rect.y <= r.y + r.h &&
		rect.h + rect.y >= r.y);


	/*if (((rect.x >= r.x && rect.x <= r.x + r.w) || (rect.x + rect.w >= r.x && rect.x + rect.w <= r.x + r.w)) && ((rect.y + rect.h < (r.y + (r.h / 4))) && (rect.y + rect.h >= r.y)))
	{
		return collisionPosition::down;
	}
	if ((rect.x + rect.w >= r.x && rect.x + rect.w < (r.x + (rect.w / 4))) && ((rect.y >= r.y && rect.y <= r.y + r.h) || (rect.y + rect.h >= r.y && rect.y + rect.h <= r.y + r.h)))
	{
		return collisionPosition::right;
	}
	if ((rect.x > (r.x + (r.w / 4)) && (rect.x <= r.x + r.w)) && ((rect.y > r.y) && (rect.y < r.y + r.h)) || (rect.y + rect.h > r.y&& rect.y + rect.h < r.y + r.h))
	{
		return collisionPosition::left;
	}*/
	


	
	
}
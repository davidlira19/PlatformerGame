#include "Collider.h"
#include "App.h"
#include "Player.h"

Collider::Collider(SDL_Rect rectangle, Type type, Module* listener) : rect(rectangle), type(type), listener(listener)
{
	
}
Collider::~Collider() 
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
}
#include "Collisions.h"

#include "App.h"

#include "Render.h"
#include "Input.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i) 
	{
		colliders[i] = nullptr;
	}
		
	matrix[Collider::Type::FLOOR][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::FLOOR][Collider::Type::WALL] = false;
	matrix[Collider::Type::FLOOR][Collider::Type::PLAYERRIHGT] = true;

	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYERRIHGT] = false;

	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::FLOOR] = false;
	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYERRIHGT] = true;

	matrix[Collider::Type::PLAYERRIHGT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYERRIHGT][Collider::Type::FLOOR] = true;
	matrix[Collider::Type::PLAYERRIHGT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYERRIHGT][Collider::Type::PLAYERRIHGT] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];
			collisionPosition position = collisionPosition::null;
			position = c1->Intersects(c2->rect);
			if (position!= collisionPosition::null)
			{
				
				if (matrix[c1->type][c2->type] == true && c1->listener != nullptr)
					c1->listener->OnCollision(c1, c2,position);

				if (matrix[c2->type][c1->type] == true && c2->listener != nullptr)
					c2->listener->OnCollision(c2, c1,position);
			}
		}
	}

	return true;
}

bool ModuleCollisions::Update()
{

	return true;
}

bool ModuleCollisions::PostUpdate()
{

	return true;
}


// Called before quitting
bool ModuleCollisions::CleanUp()
{
	

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

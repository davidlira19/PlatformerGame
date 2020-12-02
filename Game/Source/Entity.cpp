#include "Entity.h"
#include"Textures.h"
#include "App.h"
//#include "Collisions.h"
//#include "ModuleParticles.h"
#include "Player.h"
#include "EntityManager.h"
#include "Audio.h"
#include"Map.h"
#include "Render.h"

Entity::Entity(int x, int y) : position(x, y)
{
	counter = false;
	numCounter = 0;
}

Entity::~Entity()
{
	
}

/*const Collider* Enem::GetCollider() const
{
	return collider;
}*/
void Entity::Update()
{
	
	if (type == EntityTipe::EnemyAir || type == EntityTipe::EnemyGround) {
		numCounter++;
		//app->player->HasThePlayerMove()==true
		if (numCounter %5==0)
		{	
			path.ResetPath();
			//hacer reset path
			path.start = app->map->WorldToMap(position.x, position.y);

			path.goal = app->map->WorldToMap(app->player->Position.x+40, app->player->Position.y);
			path.frontier.Push(path.start);
			path.visited.Add(path.start);
			if (path.PropagateAStar() == true) 
			{
				counter = true;
			}
			else 
			{
				counter = false;
			}
			
		}
		if (counter == true) {
			iPoint nextTile;
			ListItem<iPoint>* auxiliar;
			iPoint positionn = app->map->WorldToMap(position.x, position.y);
			auxiliar = path.finalPath.end;
			while (auxiliar != nullptr)
			{
				if (auxiliar->data == positionn)
				{
					nextTile = auxiliar->prev->data;
					break;
				}
				else
				{
					auxiliar = auxiliar->prev;
				}

			}
			if (app->map->numberToMap(position.x) < nextTile.x)
			{

				position.x += 5;
			}
			else if (app->map->numberToMap(position.x) > nextTile.x)
			{
				position.x -= 5;
			}
			if (app->map->numberToMap(position.y) < nextTile.y)
			{
				position.y += 5;
			}
			else if (app->map->numberToMap(position.y) > nextTile.y)
			{
				position.y -= 5;
			}
			counter = false;
		}
	}
}

void Entity::Draw()
{
}

void Entity::OnCollision(Collider* collideri, Collider* collidere)
{
	if (collideri->type == Collider::ENEMY1) 
	{
		if (collidere->type == Collider::PLAYER) 
		{
			if (type == EntityTipe::EnemyAir)
			{
				app->player->points += 300;
			}
			if (type == EntityTipe::EnemyGround)
			{
				app->player->points += 200;
			}
			pendientedeelim = true;
		}
		
	}
	if (collidere->type == Collider::PLAYER || collidere->type == Collider::PLAYERLEFT || collidere->type == Collider::PLAYERRIGHT)
	{
		if (collideri->type == Collider::COIN ||collideri->type == Collider::HEARTH)
		{
			pendientedeelim = true;
		}

	}
}

void Entity::destr()
{
}

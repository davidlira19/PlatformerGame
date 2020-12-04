#include "Entity.h"
#include "Textures.h"
#include "App.h"
//#include "Collisions.h"
//#include "ModuleParticles.h"
#include "Player.h"
#include "EntityManager.h"
#include "Audio.h"
#include "Map.h"
#include "Render.h"
#include "Input.h"

Entity::Entity(int x, int y) : position(x, y)
{
	counter = false;
	numCounter = 0;
	left = true;
	drawPath = false;
	birdFx = app->audio->LoadFx("Assets/audio/fx/fall.wav");
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
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		if (drawPath == true)
		{
			drawPath = false;
		}
		else
		{
			drawPath = true;
		}
	}
	if (app->player->godMode == false)
	{
		if (type == EntityTipe::EnemyAir || type == EntityTipe::EnemyGround) {
			numCounter++;
			//app->player->HasThePlayerMove()==true
			if (app->player->HasThePlayerMove() == true || numCounter == 1)
			{
				path.ResetPath();
				//hacer reset path
				if (type == EntityTipe::EnemyAir) 
				{
					path.start = app->map->WorldToMap(position.x, position.y);
				}
				else 
				{
					path.start = app->map->WorldToMap(position.x, position.y);
				}
				

				path.goal = app->map->WorldToMap(app->player->Position.x + 64, app->player->Position.y+128);
				path.frontier.Push(path.start);
				path.visited.Add(path.start);
				path.PropagateAStar();


			}
			if (path.ExistPath() == true) 
			{
				if (drawPath == true)
				{
					path.DrawPath();
				}
				iPoint nextTile;
				ListItem<iPoint>* auxiliar;
				iPoint positionn = app->map->WorldToMap(position.x, position.y);
				auxiliar = path.finalPath.end;
				while (auxiliar != nullptr)
				{
					if (auxiliar->data == positionn)
					{
						if (auxiliar->prev != nullptr)
						{
							nextTile = auxiliar->prev->data;
						}
						break;
					}
					else
					{
						auxiliar = auxiliar->prev;
					}

				}
				if (deadZ == false)
				{
					if (type == EntityTipe::EnemyGround)
					{
						if (((app->player->Position.y > position.y - 64) || (app->player->Position.y < position.y + 64)) &&(app->player->Position.x < position.x + 200)  && app->map->numberToMap(position.x) < nextTile.x )
						{
							if (app->map->GetTileIdFromPosition(nextTile.x, nextTile.y, "collisions") == 64) 
							{
								position.x += 2;
							}
							
						}
						else if (((app->player->Position.y > position.y - 64) || (app->player->Position.y < position.y + 64)) && (app->player->Position.x > position.x - 200) && app->map->numberToMap(position.x) > nextTile.x )
						{
							if (app->map->GetTileIdFromPosition(nextTile.x, nextTile.y, "collisions") == 64) 
							{
								position.x -= 2;
							}
							
						}
						else 
						{
							if (left == true)
							{
								if (app->map->GetTileIdFromPosition(((position.x-10)/64) , position.y/64, "collisions") == 64)
								{
									position.x -= 1;
								}
								else
								{
									left = false;
								}
							}
							else 
							{
								if (app->map->GetTileIdFromPosition(((position.x +30)/64), position.y/64, "collisions") == 64)
								{
									position.x += 1;
								}
								else 
								{
									left = true;
								}
							}		
						}
						
				
					}
					if (type == EntityTipe::EnemyAir)
					{
						if (app->map->numberToMap(position.x) < nextTile.x )
						{
							position.x += 2;
						}
						else if (app->map->numberToMap(position.x) > nextTile.x)
						{
							position.x -= 2;
						}

						if (app->map->numberToMap(position.y) < nextTile.y)
						{
							position.y += 2;
						}
						else if (app->map->numberToMap(position.y) > nextTile.y)
						{
							position.y -= 2;
						}
					}
					counter = false;
				}
			}
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
				app->audio->PlayFx(birdFx);
				app->player->points += 300;
			}
			pendientedeelim = true;
		}
		
	}
	if (collidere->type == Collider::PLAYER || collidere->type == Collider::PLAYERLEFT || collidere->type == Collider::PLAYERRIGHT)
	{
		if (collideri->type == Collider::COIN ||collideri->type == Collider::HEART)
		{
			pendientedeelim = true;
		}

	}
}

void Entity::destr()
{
}

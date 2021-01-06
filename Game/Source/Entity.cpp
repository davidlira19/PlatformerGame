#include "Entity.h"
#include "Textures.h"
#include "App.h"
#include "Player.h"
#include "EntityManager.h"
#include "Audio.h"
#include "Map.h"
#include "Render.h"
#include "Input.h"

Entity::Entity(int x, int y) : position(x, y)
{
	dire = -1;
	counter = false;
	numCounter = 0;
	left = true;
	if (app->entity->drawItems == false) 
	{
		drawPath = false;
	}
	else 
	{
		drawPath = true;
	}
}

Entity::~Entity() {}

void Entity::Update(float dt)
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
		if (type == EntityTipe::EnemyAir || type == EntityTipe::EnemyGround) 
		{
			if (numCounter <= 30) 
			{
				numCounter++;
			}
			
			if (app->player->HasThePlayerMove() == true || numCounter == 30)
			{
				path.ResetPath();
				if (type == EntityTipe::EnemyAir) 
				{
					path.start = app->map->WorldToMap(position.x, position.y);
				}
				else 
				{
					path.start = app->map->WorldToMap(position.x, position.y);
				}

				path.goal = app->map->WorldToMap(app->player->position.x + 64, app->player->position.y + 50);
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
						if (((app->player->position.y > position.y - 64) || (app->player->position.y < position.y + 64)) &&(app->player->position.x < position.x + 200)  && app->map->numberToMap(position.x) < nextTile.x )
						{
							if (app->map->GetTileIdFromPosition(nextTile.x, nextTile.y, "collisions") == 64) 
							{
								dire = 1;
								position.x += 150 * (dt / 1000);
							}
						}
						else if (((app->player->position.y > position.y - 64) || (app->player->position.y < position.y + 64)) && (app->player->position.x > position.x - 200) && app->map->numberToMap(position.x) > nextTile.x )
						{
							if (app->map->GetTileIdFromPosition(nextTile.x, nextTile.y, "collisions") == 64) 
							{
								dire = -1;
								position.x -= 150 * (dt / 1000);
							}
						}
						else 
						{
							if (left == true)
							{
								if (app->map->GetTileIdFromPosition(((position.x - 10) / 64), position.y / 64, "collisions") == 64)
								{
									dire = -1;
									position.x -= 100 * (dt / 1000);
								}
								else
								{
									left = false;
								}
							}
							else 
							{
								if (app->map->GetTileIdFromPosition(((position.x + 30) / 64), position.y / 64, "collisions") == 64)
								{
									dire = 1;
									position.x += 100 * (dt / 1000);
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
							dire = 1;
							position.x += 150 * (dt / 1000);
						}
						else if (app->map->numberToMap(position.x) > nextTile.x)
						{
							dire = -1;
							position.x -= 150 * (dt / 1000);
						}

						if (app->map->numberToMap(position.y) < nextTile.y)
						{
							dire = 1;
							position.y += 150 * (dt / 1000);
						}
						else if (app->map->numberToMap(position.y) > nextTile.y)
						{
							dire = -1;
							position.y -= 150 * (dt / 1000);
						}
					}
					counter = false;
				}
			}
		}
	}
}

void Entity::Draw() {}

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
			pendienteDeElim = true;
		}
	}
	if (collidere->type == Collider::PLAYER || collidere->type == Collider::PLAYERLEFT || collidere->type == Collider::PLAYERRIGHT)
	{
		if (collideri->type == Collider::COIN ||collideri->type == Collider::HEART)
		{
			app->SaveGameRequest("save_game.xml");
			pendienteDeElim = true;
		}
	}
}

void Entity::destr() {}
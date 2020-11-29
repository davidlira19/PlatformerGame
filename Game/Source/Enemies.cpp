#include "Enemies.h"

#include "App.h"
#include"Player.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Log.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include<time.h>

#define SPAWN_MARGIN 50


Enemy::Enemy(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	
	/*enemigos = app->tex->Load("Assets/objetosanimados.png");
	kongs = app->tex->Load("Assets/sprites.png");
	enemyDestroyedFx = app->audio->LoadFx("Assets/8. SFX (Kill).wav");*/

	return true;
}

bool Enemy::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	/*for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr && enemies[i]->pendientedeelim == true)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}*/

	return true;
}

bool Enemy::Update(float dt)
{
	/*HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Update(dt);
	}

	HandleEnemiesDespawn();*/

	return true;
}

bool Enemy::PostUpdate()
{
	/*for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}*/

	return true;
}

// Called before quitting
bool Enemy::CleanUp()
{
	/*LOG("Freeing all enemies");
	app->tex->Unload(kongs);
	app->tex->Unload(enemigos);
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}*/

	return true;
}

bool Enemy::AddEnemy(Enemy_Type type, int x, int y,int direccion)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			spawnQueue[i].direccion = direccion;
			ret = true;
			break;
		}
	}

	return ret;
}

/*void Enemy::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			SpawnEnemy(spawnQueue[i]);
			spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
		}
	}
}*/

/*void Enemy::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr&&enemies[i]->pendientedeelim==true)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}
}*/

/*void Enemy::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == nullptr)
		{

			switch (info.type)
			{
			case Enemy_Type::Ground:
				enemies[i] = new Enemy_Ground(info.x, info.y, info.direccion);
				enemies[i]->ground = grounds;
				enemies[i]->destroyedFx = enemyDestroyedFx;
				break;

			case Enemy_Type::Air:
				enemies[i] = new Enemy_Air(info.x, info.y, info.direccion);
				enemies[i]->air = airs;
				enemies[i]->destroyedFx = enemyDestroyedFx;
				break;
			}
			break;
		}
	}
}*/

/*void Enemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (c1->type == c1->Enemigo && c2->type == c2->martillo) {
				if (c1 == enemies[i]->GetCollider()) {
					App->audio->PlayFx(App->enemies->enemyDestroyedFx);//Notify the enemy of a collision
					enemies[i]->destr();
					break;
				}	
			}
			else {
				enemies[i]->OnCollision(c1, c2);
			}

		}

	}
}*/

/*bool Enemy::compene()
{
	for (int i = 0; i < MAX_ENEMIES; i++) 
	{
		if (enemies[i] != nullptr) 
		{
			return false;
		}
	}
	return true;
}*/
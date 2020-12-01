#include "Enemies.h"
#include "App.h"
#include"Player.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Log.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"


#define SPAWN_MARGIN 50


EntityManager::EntityManager(bool startEnabled) : Module(startEnabled)
{
	/*for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;*/
}

EntityManager::~EntityManager()
{

}

bool EntityManager::Start()
{

	textures = app->tex->Load("Assets/textures/bird_animation.png");

	return true;
}

bool EntityManager::PreUpdate()
{
	// Remove all enemies scheduled for deletion

	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) {
		if (listItem->data->pendientedeelim == true)
		{
			entityList.Del(listItem);
		}
		listItem = listItem->next;
	}
	return true;
}

bool EntityManager::Update(float dt)
{
	HandleEnemiesSpawn();

	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) {
		listItem->data->Update();
		listItem = listItem->next;
	}

	HandleEnemiesDespawn();

	return true;
}

bool EntityManager::PostUpdate()
{
	/*for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}*/
	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) {
		listItem->data->Draw();
		listItem = listItem->next;
	}

	return true;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	LOG("Freeing all enemies");
	app->tex->UnLoad(textures);
	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) {
		delete listItem->data;	
		listItem = listItem->next;
	}
	entityList.Clear();
	return true;
}

bool EntityManager::AddEntity(EntityTipe type, int x, int y)
{
	bool ret = false;

	for(int i=0;i< MAX_ENEMIES;i++)
	{
		if (spawnQueue[i].type == EntityTipe::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}
	return ret;
}

void EntityManager::HandleEnemiesSpawn()
{
	for(int i=0;i<MAX_ENEMIES;i++)
	{
		if (spawnQueue[i].type != EntityTipe::NO_TYPE)
		{
			SpawnEnemy(spawnQueue[i]);
			spawnQueue[i].type = EntityTipe::NO_TYPE; // Removing the newly spawned enemy from the queue
		}

	}
}

void EntityManager::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	//for (int i = 0; i < MAX_ENEMIES; i++)
	//{
	//	if (enemies[i] != nullptr&&enemies[i]->pendientedeelim==true)
	//	{
	//		delete enemies[i];
	//		enemies[i] = nullptr;
	//	}
	//}
	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) {
		if (listItem->data->pendientedeelim == true)
		{
			delete listItem->data;
			entityList.Del(listItem);
		}
		listItem = listItem->next;
	}
}

void EntityManager::SpawnEnemy(const EnemySpawnpoint& info)
{
	Entity* entity = nullptr;
	switch (info.type)
	{
	case EntityTipe::EnemyAir:
		entity = new EnemyAir(info.x, info.y);
		entity->airEnemiesTexture = textures;
		break;
	case EntityTipe::EnemyGround:
		entity = new EnemyGround(info.x, info.y);
		entity->airEnemiesTexture = textures;
		break;
	}
	entity->type = info.type;
	entityList.Add(entity);
}

/*void Enemies::OnCollision(Collider* c1, Collider* c2)
{

}

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
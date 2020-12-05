#include "EntityManager.h"
#include "App.h"
#include "Player.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Log.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"

#define SPAWN_MARGIN 50

EntityManager::EntityManager(bool startEnabled) : Module(startEnabled)
{
	name.Create("EntityManager");
}

EntityManager::~EntityManager() {}

bool EntityManager::Start()
{

	birdTexture = app->tex->Load("Assets/textures/bird_animation.png");
	zombieTexture = app->tex->Load("Assets/textures/zombie_animation.png");
	coinTexture = app->tex->Load("Assets/textures/coin_animation.png");
	heartTexture = app->tex->Load("Assets/textures/heart_animation.png");

	drawItems = false;

	return true;
}

bool EntityManager::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) 
	{
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
	while (listItem != nullptr) 
	{
		listItem->data->Update();
		listItem = listItem->next;
	}

	HandleEnemiesDespawn();

	return true;
}

bool EntityManager::PostUpdate()
{
	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) 
	{
		listItem->data->Draw();
		listItem = listItem->next;
	}

	return true;
}

// Called before quitting
bool EntityManager::CleanUp()
{
	LOG("Freeing all enemies");
	app->tex->UnLoad(birdTexture);
	app->tex->UnLoad(zombieTexture);
	app->tex->UnLoad(coinTexture);
	app->tex->UnLoad(heartTexture);
	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) 
	{
		listItem->data->path.ResetPath();
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
			spawnQueue[i].type = EntityTipe::NO_TYPE;
		}

	}
}

void EntityManager::HandleEnemiesDespawn()
{
	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) 
	{
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
		entity->airEnemiesTexture = birdTexture;
		break;
	case EntityTipe::EnemyGround:
		entity = new EnemyGround(info.x, info.y);
		entity->groundEnemiesTexture = zombieTexture;
		break;
	case EntityTipe::Coin:
		entity = new Coin(info.x, info.y);
		entity->moneyTexture = coinTexture;
		break;
	case EntityTipe::Heart:
		entity = new Heart(info.x, info.y);
		entity->lifeTexture = heartTexture;
		break;
	}
	entity->type = info.type;
	entityList.Add(entity);
}

void EntityManager::OnCollision(Collider* c1, Collider* c2)
{
	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) 
	{
		if (c1->type == c1->ENEMY2)
		{
			if (c2->type == c2->PLAYERLEFT || c2->type == c2->PLAYERRIGHT)
			{
				break;
			}
		}
		else if (c1->type == c1->ENEMY1)
		{
			if (c2->type == c2->PLAYER)
			{
				if (c1 == listItem->data->playerWin)
				{
					listItem->data->OnCollision(c1,c2);
				}
			}
		}
		else if (c1->type == c1->COIN || c1->type == c1->HEART)
		{
			if (c2->type == c2->PLAYER || c2->type == c2->PLAYERLEFT || c2->type == c2->PLAYERRIGHT)
			{
				if (c1 == listItem->data->collider)
				{
					listItem->data->OnCollision(c1, c2);
				}
			}
		}
		listItem = listItem->next;
	}
}

bool EntityManager::LoadState(pugi::xml_node* nodo)
{
	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) {
		listItem->data->path.ResetPath();
		delete listItem->data;
		listItem = listItem->next;
	}
	entityList.Clear();
	pugi::xml_node auxiliar;
	auxiliar = nodo->child("data");
	int num = auxiliar.attribute("num").as_int();
	auxiliar = auxiliar.child("Enemy");
	EntityTipe auxiliarTipe = EntityTipe::EnemyAir;
	for (int i = 0; i < num; i++)
	{
		SString string = auxiliar.attribute("type").as_string();
		if (string == "EnemyAir")
		{
			auxiliarTipe = EntityTipe::EnemyAir;
		}
		else if (string == "EnemyGround")
		{
			auxiliarTipe = EntityTipe::EnemyGround;
		}
		else if (string == "Coin")
		{
			auxiliarTipe = EntityTipe::Coin;
		}
		else if (string == "Heart")
		{
			auxiliarTipe = EntityTipe::Heart;
		}
		AddEntity(auxiliarTipe, auxiliar.attribute("x").as_int(), auxiliar.attribute("y").as_int());
		auxiliar = auxiliar.next_sibling();
	}
	return true;
}

bool EntityManager::SaveState(pugi::xml_node* nodo)
{
	int num = entityList.count();
	ListItem<Entity*>* list;
	pugi::xml_node auxiliar;
	auxiliar = nodo->append_child("data");
	list = entityList.start;
	auxiliar.append_attribute("num").set_value(num);
	while (list != nullptr)
	{
		auxiliar.append_child("Enemy").append_attribute("x").set_value(list->data->position.x);
		auxiliar.last_child().append_attribute("y").set_value(list->data->position.y);
		if (list->data->type == EntityTipe::EnemyAir)
		{
			auxiliar.last_child().append_attribute("type").set_value("EnemyAir");
		}
		else if (list->data->type == EntityTipe::EnemyGround)
		{
			auxiliar.last_child().append_attribute("type").set_value("EnemyGround");
		}
		else if (list->data->type == EntityTipe::Coin)
		{
			auxiliar.last_child().append_attribute("type").set_value("Coin");
		}
		else if (list->data->type == EntityTipe::Heart)
		{
			auxiliar.last_child().append_attribute("type").set_value("Heart");
		}
		list = list->next;
	}
	return true;
}
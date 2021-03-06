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

bool EntityManager::Start(bool newGame)
{

	birdTexture = app->tex->Load("Assets/Textures/bird_animation.png");
	zombieTexture = app->tex->Load("Assets/Textures/zombie_animation.png");
	coinTexture = app->tex->Load("Assets/Textures/coin_animation.png");
	heartTexture = app->tex->Load("Assets/Textures/heart_animation.png");
	birdFx = app->audio->LoadFx("Assets/Audio/Fx/fall.wav");
	zombieFx = app->audio->LoadFx("Assets/Audio/Fx/zombie_pain.wav");

	drawItems = false;

	return true;
}

bool EntityManager::PreUpdate()
{
	
	return true;
}

bool EntityManager::Update(float dt)
{
	HandleEnemiesSpawn();

	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) 
	{
		listItem->data->Update(dt);
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
	app->audio->Unload(birdFx);
	app->audio->Unload(zombieFx);
	
	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) 
	{
		//listItem->data->path.ResetPath();
		delete listItem->data;	
		listItem = listItem->next;
	}
	entityList.Clear();
	return true;
}

bool EntityManager::AddEntity(EntityType type, int x, int y)
{
	bool ret = false;

	for(int i=0;i< MAX_ENEMIES;i++)
	{
		if (spawnQueue[i].type == EntityType::NO_TYPE)
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
		if (spawnQueue[i].type != EntityType::NO_TYPE)
		{
			SpawnEnemy(spawnQueue[i]);
			spawnQueue[i].type = EntityType::NO_TYPE;
		}

	}
}

void EntityManager::HandleEnemiesDespawn()
{
	ListItem<Entity*>* listItem;
	listItem = entityList.start;
	while (listItem != nullptr) 
	{
		if (listItem->data->pendienteDeElim == true)
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
	case EntityType::ENEMY_AIR:
		entity = new EnemyAir(info.x, info.y);
		entity->airEnemiesTexture = birdTexture;
		entity->birdFx = birdFx;
		break;
	case EntityType::ENEMY_GROUND:
		entity = new EnemyGround(info.x, info.y);
		entity->groundEnemiesTexture = zombieTexture;
		entity->zombieFx = zombieFx;
		break;
	case EntityType::COIN:
		entity = new Coin(info.x, info.y);
		entity->moneyTexture = coinTexture;
		break;
	case EntityType::HEART:
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
	while (listItem != nullptr) 
	{
		//listItem->data->path.ResetPath();
		delete listItem->data;
		entityList.Del(listItem);
		listItem = listItem->next;
	}
	//entityList.Clear();
	pugi::xml_node auxiliar;
	auxiliar = nodo->child("data");
	int num = auxiliar.attribute("num").as_int();
	auxiliar = auxiliar.child("Enemy");
	EntityType auxiliarTipe = EntityType::ENEMY_AIR;
	for (int i = 0; i < num; i++)
	{
		SString string = auxiliar.attribute("type").as_string();
		if (string == "EnemyAir")
		{
			auxiliarTipe = EntityType::ENEMY_AIR;
		}
		else if (string == "EnemyGround")
		{
			auxiliarTipe = EntityType::ENEMY_GROUND;
		}
		else if (string == "Coin")
		{
			auxiliarTipe = EntityType::COIN;
		}
		else if (string == "Heart")
		{
			auxiliarTipe = EntityType::HEART;
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
		if (list->data->type == EntityType::ENEMY_AIR)
		{
			auxiliar.last_child().append_attribute("type").set_value("EnemyAir");
		}
		else if (list->data->type == EntityType::ENEMY_GROUND)
		{
			auxiliar.last_child().append_attribute("type").set_value("EnemyGround");
		}
		else if (list->data->type == EntityType::COIN)
		{
			auxiliar.last_child().append_attribute("type").set_value("Coin");
		}
		else if (list->data->type == EntityType::HEART)
		{
			auxiliar.last_child().append_attribute("type").set_value("Heart");
		}
		list = list->next;
	}
	return true;
}
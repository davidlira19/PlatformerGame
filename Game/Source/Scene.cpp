#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Scene2.h"
#include "Map.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"
#include "Collisions.h"
#include "FadeToBlack.h"
#include "EntityManager.h"
#include "PathFinding.h"

Scene::Scene(bool startEnabled) : Module(startEnabled)
{
	name.Create("scene");
}

// Destructor
Scene::~Scene() {}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// Load map
	app->map->Enable();
	app->map->Load("snow_tileset.tmx");

	// Load music
	app->audio->Enable();
	app->audio->PlayMusic("Assets/audio/music/christmas_music.ogg");

	//Load Position
	app->render->camera.x = -580;
	app->render->camera.y = -250;
	app->player->currentLevel = 1;

	//Player position
	app->player->position.x = 2300 / 2;
	app->player->position.y = 1060 / 2;

	//Load Texture
	bg_snow = app->tex->Load("Assets/textures/snow_background.png");
	freeCamera = false;
	app->collisions->Enable();
	app->player->Enable();
	app->entity->Enable();
	SDL_Rect rect;

	for (int y = 0; y < app->map->data.tilesets.start->data->numTilesHeight; y++)
	{
		for (int x =0 ; x < app->map->data.tilesets.start->data->numTilesWidth; x++)
		{
			if (app->map->GetTileIdFromPosition(x, y, "collisions") == 61)
			{
				rect = { x* app->map->data.tilesets.start->data->tileWidth ,y* app->map->data.tilesets.start->data->tileHeight,app->map->data.tilesets.start->data->tileWidth,app->map->data.tilesets.start->data->tileHeight };
				colliders.Add(app->collisions->AddCollider(rect, Collider::FLOOR));
			}
			if (app->map->GetTileIdFromPosition(x, y, "collisions") == 62) 
			{
				rect = { x * app->map->data.tilesets.start->data->tileWidth ,y * app->map->data.tilesets.start->data->tileHeight,app->map->data.tilesets.start->data->tileWidth,app->map->data.tilesets.start->data->tileHeight };
				colliders.Add(app->collisions->AddCollider(rect, Collider::WALL));
			}
			if (app->map->GetTileIdFromPosition(x, y, "collisions") == 63)
			{
				rect = { x * app->map->data.tilesets.start->data->tileWidth ,y * app->map->data.tilesets.start->data->tileHeight,app->map->data.tilesets.start->data->tileWidth,app->map->data.tilesets.start->data->tileHeight };
				colliders.Add(app->collisions->AddCollider(rect, Collider::CHECKPOINT,(Module*)app->player));
			}
		}
	}

	//BIRDS
	app->entity->AddEntity(EntityTipe::EnemyAir, 1633, 200);
	app->entity->AddEntity(EntityTipe::EnemyAir, 3343, 670);
	app->entity->AddEntity(EntityTipe::EnemyAir, 4300, 550);
	app->entity->AddEntity(EntityTipe::EnemyAir, 5005, 560);

	//ZOMBIES
	app->entity->AddEntity(EntityTipe::EnemyGround, 1876, 456);
	app->entity->AddEntity(EntityTipe::EnemyGround, 3022, 776);
	app->entity->AddEntity(EntityTipe::EnemyGround, 3839, 650);
	app->entity->AddEntity(EntityTipe::EnemyGround, 4619, 519);

	//COIN
	app->entity->AddEntity(EntityTipe::Coin, 1860, 435);
	app->entity->AddEntity(EntityTipe::Coin, 3000, 755);
	app->entity->AddEntity(EntityTipe::Coin, 100, 100);

	//HEART
	app->entity->AddEntity(EntityTipe::Heart, 1000, 435);
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	ListItem<Collider*>* auxiliar;
	auxiliar = colliders.start;
	for (int y = 0; y < app->map->data.tilesets.start->data->numTilesHeight; y++)
	{
		for (int x = 0; x < app->map->data.tilesets.start->data->numTilesWidth; x++)
		{
			
			if ((app->map->GetTileIdFromPosition(x, y, "collisions") == 61 || app->map->GetTileIdFromPosition(x, y, "collisions") == 62) || app->map->GetTileIdFromPosition(x, y, "collisions") == 63 && auxiliar!=NULL)
			{		
				auxiliar->data->SetPos(x * app->map->data.tilesets.start->data->tileWidth+app->render->camera.x, y * app->map->data.tilesets.start->data->tileHeight + app->render->camera.y);
				auxiliar = auxiliar->next;
			}
		}
	}

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	if (freeCamera == false)
	{
		app->render->camera.x = (app->player->position.x - 500) * -1;
		app->render->camera.y = (app->player->position.y - 250) * -1;
	}

	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		app->map->ChangeCollisionsDraw();

		if (app->entity->drawItems == true)
		{
			app->entity->drawItems = false;
		}
		else if (app->entity->drawItems == false)
		{
			app->entity->drawItems = true;
		}
	}

	if ((app->player->position.x >= 1000 && app->player->position.x <= 2140 && app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) || (app->player->position.x >= 4900 && app->player->position.x <= 5700 && app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN))
	{
		app->player->position.x = 2141;
		app->player->position.y = 435;
	}

	else if (app->player->position.x >= 2141 && app->player->position.x <= 4903 && app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
	{
		app->player->position.x = 4900;
		app->player->position.y = 563;
	}

	//CAMERA.X LIMITS
	if (app->render->camera.x > 0)
	{
		app->render->camera.x = 0;
	}
	else if (app->render->camera.x <= -8200)
	{
		app->render->camera.x = -8200;
	}

	//CAMERA.Y LIMITS
	if (app->render->camera.y >= -5)
	{
		app->render->camera.y = -5;
	}
	else if (app->render->camera.y <= -1100)
	{
		app->render->camera.y = -1100;
	}
	
	//CAMERA AUTOMATIC MOVEMENT
	if (app->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		if (freeCamera == true)
		{
			freeCamera = false;
		}
		else
		{
			freeCamera = true;
		}
	}

	if (freeCamera == true)
	{
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			app->render->camera.y += 500 * (dt / 1000);

		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			app->render->camera.y -= 500 * (dt / 1000);

		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			app->render->camera.x += 500 * (dt / 1000);

		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			app->render->camera.x -= 500 * (dt/1000);
	}

	//DRAW BACKGROUND
	app->render->DrawTexture(bg_snow, -3600/2, 0);
	app->render->DrawTexture(bg_snow, 0, 0);
	app->render->DrawTexture(bg_snow, 3600/2, 0);
	app->render->DrawTexture(bg_snow, 7200/2, 0);
	app->render->DrawTexture(bg_snow, 10800/2, 0);
	app->map->Draw();

	//CONDITIONS TO WIN - LOSE
	if (app->player->position.y >= 1602 / 2)
	{
		app->player->dead = true;
		app->player->lifes--;
	}
	if (app->player->position.x >= 11350 / 2)
	{
		app->player->win = true;
	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;
	
	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	app->render->camera.x = 0;
	app->render->camera.y = 0;
	app->tex->UnLoad(bg_snow);
	app->map->Disable();
	app->entity->Disable();
	app->audio->Unload();
	app->audio->Disable();
	app->collisions->Disable();
	colliders.Clear();
	
	return true;
}
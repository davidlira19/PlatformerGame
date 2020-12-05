#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene2.h"
#include "Map.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"
#include "Collisions.h"
#include "EntityManager.h"

Scene2::Scene2(bool startEnabled) : Module(startEnabled)
{
	name.Create("scene2");
}

// Destructor
Scene2::~Scene2() {}

// Called before render is available
bool Scene2::Awake()
{
	LOG("Loading Scene2");
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool Scene2::Start()
{
	// Load map
	app->map->Enable();
	app->map->Load("snow_tileset_lvl2.tmx");

	app->audio->Enable();
	app->audio->PlayMusic("Assets/audio/music/christmas_music.ogg");

	//Load Position
	app->render->camera.x = 0;
	app->render->camera.y = 0;
	app->player->currentLevel = 2;

	//Player position
	app->player->position.x = 600;
	app->player->position.y = 100;

	//Load Texture
	bg_snow = app->tex->Load("Assets/textures/snow_background.png");
	freeCamera = false;
	app->collisions->Enable();
	app->player->Enable();
	app->entity->Enable();
	SDL_Rect rect;

	for (int y = 0; y < app->map->data.tilesets.start->data->numTilesHeight; y++)
	{
		for (int x = 0; x < app->map->data.tilesets.start->data->numTilesWidth; x++)
		{
			if (app->map->GetTileIdFromPosition(x, y, "collisions") == 61)
			{
				rect = { x * app->map->data.tilesets.start->data->tileWidth ,y * app->map->data.tilesets.start->data->tileHeight,app->map->data.tilesets.start->data->tileWidth,app->map->data.tilesets.start->data->tileHeight };
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
				colliders.Add(app->collisions->AddCollider(rect, Collider::CHECKPOINT, (Module*)app->player));
			}
		}
	}

	//BIRDS
	app->entity->AddEntity(EntityTipe::EnemyAir, 5771, 809);
	app->entity->AddEntity(EntityTipe::EnemyAir, 3528, 386);
	app->entity->AddEntity(EntityTipe::EnemyAir, 1975, 671);

	//ZOMBIES
	app->entity->AddEntity(EntityTipe::EnemyGround, 4766, 1226);
	app->entity->AddEntity(EntityTipe::EnemyGround, 5977, 1034);
	app->entity->AddEntity(EntityTipe::EnemyGround, 1814, 1163);

	//COIN
	app->entity->AddEntity(EntityTipe::Coin, 2562, 681);
	app->entity->AddEntity(EntityTipe::Coin, 1971, 1066);

	//HEART
	app->entity->AddEntity(EntityTipe::Heart, 692, 925);
	return true;
}

// Called each loop iteration
bool Scene2::PreUpdate()
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
bool Scene2::Update(float dt)
{
	if ((app->player->position.x >= 0 && app->player->position.x <= 2264 && app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) || (app->player->position.x >= 4107 && app->player->position.x <= 10000 && app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN))
	{
		app->player->position.x = 2465;
		app->player->position.y = 1199;
	}
	else if (app->player->position.x >= 2465 && app->player->position.x <= 4108 && app->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
	{
		app->player->position.x = 4108;
		app->player->position.y = 751;
	}
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

	//CAMERA.X LIMITS
	if (app->render->camera.x > 0)
	{
		app->render->camera.x = 0;
	}
	else if (app->render->camera.x <= -5860)
	{
		app->render->camera.x = -5860;
	}

	//CAMERA.Y LIMITS
	if (app->render->camera.y <= -1000)
	{
		app->render->camera.y = -1000;
	}
	else if (app->render->camera.y >= 0)
	{
		app->render->camera.y = 0;
	}

	//CAMERA AUTOMATIC MOVEMENT
	if (app->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		if (freeCamera == true)
		{
			freeCamera = false;
		}
		else if(freeCamera == false)
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
			app->render->camera.x -= 500 * (dt / 1000);
	}

	//DRAW BACKGROUND
	app->render->DrawTexture(bg_snow, -3600/2, 0);
	app->render->DrawTexture(bg_snow, 0, 0);
	app->render->DrawTexture(bg_snow, 3600/2, 0);
	app->render->DrawTexture(bg_snow, 7200/2, 0);
	app->render->DrawTexture(bg_snow, 10800/2, 0);
	app->render->DrawTexture(bg_snow, -3600 / 2, 893);
	app->render->DrawTexture(bg_snow, 0, 893);
	app->render->DrawTexture(bg_snow, 3600 / 2, 893);
	app->render->DrawTexture(bg_snow, 7200 / 2, 893);
	app->render->DrawTexture(bg_snow, 10800 / 2, 893);
	app->map->Draw();

	if (app->player->position.y >= 1310)
	{
		app->player->dead = true;
		app->player->lifes--;
	}
	if (app->player->position.x >= 6726)
	{
		app->player->win = true;
	}

	return true;
}

// Called each loop iteration
bool Scene2::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;
	
	return ret;
}

// Called before quitting
bool Scene2::CleanUp()
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
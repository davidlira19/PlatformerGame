#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
//#include "Scene.h"
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
Scene2::~Scene2()
{}

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
	// L03: DONE: Load map
	app->audio->Enable();
	app->map->Enable();
	app->map->Load("snow_tileset_lvl2.tmx");
	// Load music
	app->audio->PlayMusic("Assets/audio/music/christmas_music.ogg");
	//Load Position
	app->render->camera.x = 0;
	app->render->camera.y = 0;
	//Player position
	app->player->Position.x = 600;
	app->player->Position.y = 100;
	app->player->currentLevel = 2;
	//Load Texture
	bg_snow = app->tex->Load("Assets/textures/snow_background.png");
	//app->player->Enable();
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

	//ZOMBIES

	//COIN

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
	if (freeCamera == false)
	{
		app->render->camera.x = (app->player->Position.x - 500) * -1;
		app->render->camera.y = (app->player->Position.y - 250) * -1;
	}
	LOG("%d %d", app->player->Position.x, app->player->Position.y);
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		app->map->ChangeCollisionsDraw();

	}
	LOG("%d %d", app->render->camera.x, app->render->camera.y);
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
	if (app->render->camera.y <= -750)
	{
		app->render->camera.y = -750;
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

	//if (app->input->GetMouseButtonDown(1) == KEY_DOWN)
	//{
	//	app->input->GetMousePosition(app->map->goal.x, app->map->goal.y);
	//	app->map->goal.x -= app->render->camera.x;
	//	app->map->goal.y -= app->render->camera.y;
	//	app->map->goal = app->map->WorldToMap(app->map->goal.x, app->map->goal.y);
	//}
	//if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	//{
	//	if ((app->map->goal.x != -1) && (app->map->goal.y != -1))
	//	{
	//		app->map->PropagateBFS();
	//		//app->map->DrawPath();
	//	}
	//}
	//if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	//{
	//	if ((app->map->goal.x != -1) && (app->map->goal.y != -1))
	//	{
	//		app->map->PropagateAStar();
	//		//app->map->DrawPath();
	//	}
	//}
	//// L03: DONE 7: Set the window title with map/tileset info
	//if ((app->map->goal.x != -1) && (app->map->goal.y != -1))
	//{
	//	TileSet* tileset = app->map->GetTilesetFromTileId(62);

	//	SDL_Rect rec = tileset->GetTileRect(62);
	//	iPoint pos = app->map->MapToWorld(app->map->goal.x, app->map->goal.y);

	//	app->render->DrawTexture(tileset->texture, pos.x, pos.y, &rec);
	//	app->map->DrawPath();
	//}
	//// L03: DONE 7: Set the window title with map/tileset info
	//if (app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
	//{
	//	app->map->goal.x = -1;
	//	app->map->goal.y = -1;
	//	app->map->ResetPath();
	//	app->map->finalPath.Clear();
	//}


	//LOG("Position x: %d ------ Position y: %d", app->render->camera.x, app->render->camera.y);

	return true;
}

// Called each loop iteration
bool Scene2::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;
	
	
	/*ListItem<Collider*>* auxiliar;
	auxiliar = colliders.start;
	while (auxiliar != nullptr) {
		SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(app->render->renderer, 0, 255, 255, 80);
		SDL_RenderFillRect(app->render->renderer, &auxiliar->data->rect);
		auxiliar = auxiliar->next;
	}*/
	
		
	
	
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
	app->audio->Unload();
	colliders.Clear();
	app->collisions->Disable();
	
	
	return true;
}

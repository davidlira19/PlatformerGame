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
Scene::~Scene()
{}

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
	// L03: DONE: Load map
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
	app->player->Position.x = 2300 / 2;
	app->player->Position.y = 1060 / 2;
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
	//app->entity->AddEntity(EntityTipe::EnemyAir, 1633, 600);
	app->entity->AddEntity(EntityTipe::EnemyAir, 3343, 670);
	app->entity->AddEntity(EntityTipe::EnemyAir, 4300, 550);
	app->entity->AddEntity(EntityTipe::EnemyAir, 5005, 560);
	//ZOMBIES
	app->entity->AddEntity(EntityTipe::EnemyGround, 1876, 450);
	app->entity->AddEntity(EntityTipe::EnemyGround, 3022, 770);
	app->entity->AddEntity(EntityTipe::EnemyGround, 3839, 644);
	app->entity->AddEntity(EntityTipe::EnemyGround, 4619, 513);
	//app->entity->AddEntity(EntityTipe::EnemyGround, 5405, 513);

	/*app->entity->AddEntity(EntityTipe::EnemyGround, 1899, 435);
	app->entity->AddEntity(EntityTipe::EnemyGround, 3034, 755);
	app->entity->AddEntity(EntityTipe::EnemyGround, 3832, 628);
	app->entity->AddEntity(EntityTipe::EnemyGround, 4631, 500);
	app->entity->AddEntity(EntityTipe::EnemyGround, 5404, 499);*/
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

//bool collisions::checkIfCollision(int id, position positionToChek)
//{
//	bool result = false;
//	int idChek;
//	position numTilesMap;
//	position tilePosition;
//	/*numTilesMap.x = app->map->data.tilesets.start->data->numTilesWidth * app->map->data.tilesets.start->data->tileWidth;
//	numTilesMap.y = app->map->data.tilesets.start->data->numTilesHeight * app->map->data.tilesets.start->data->tileHeight;*/
//	numTilesMap.x = app->map->data.tilesets.start->data->tileWidth;
//	numTilesMap.y = app->map->data.tilesets.start->data->tileHeight;
//	tilePosition.x = positionToChek.x /numTilesMap.x ;
//	tilePosition.y = positionToChek.y /numTilesMap.y ;
//	ListItem<MapLayer*>* list1;
//	
//	for (list1 = app->map->data.layers.start; list1 != nullptr; list1=list1->next) 
//	{
//		if (list1->data->name == "collisions") 
//		{
//			idChek=list1->data->Get(tilePosition.x, tilePosition.y);
//
//			if (idChek == id) 
//			{
//				result = true;
//				return result;
//			}
//		}
//	}
//	return result;
//}
// Called each loop iteration
bool Scene::Update(float dt)
{
	if (freeCamera == false)
	{
		app->render->camera.x = (app->player->Position.x - 500) * -1;
		app->render->camera.y = (app->player->Position.y - 250) * -1;
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

	//CONDITIONS TO WIN - LOSE
	if (app->player->Position.y >= 1602 / 2)
	{
		app->player->Dead = true;
	}
	if (app->player->Position.x >= 11350 / 2)
	{
		app->player->Win = true;
	}

	//LOG("Position x: %d ------ Position y: %d", app->render->camera.x, app->render->camera.y);

	/*if (app->player->Win == true)
	{
		app->fade->FadeToBlack((Module*)app->scene, (Module*)app->scene2);
	}*/

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
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

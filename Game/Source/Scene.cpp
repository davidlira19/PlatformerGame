#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "FadeToBlack.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"

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
	app->map->Load("snow_tileset.tmx");
	// Load music
	app->audio->PlayMusic("Assets/audio/music/christmas_music.ogg");
	//Load Position
	app->render->camera.x = 0;
	app->render->camera.y = -700;
	//Load Texture
	bg_snow = app->tex->Load("Assets/textures/snow_background.png");

	freeCamera = false;
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}
collisionPosition collisions::getCollision(position positionChek,SDL_Rect rect,int id)
{
	bool chekResult;
	collisionPosition positionCollision = collisionPosition::null;
	position relativePosition;
	for (int a = 1; a < 4; a++) 
	{
		switch (a)
		{
		case 1:
			relativePosition.x = positionChek.x + (rect.w);
			relativePosition.y = positionChek.y + (rect.h / 2);
			chekResult = checkIfCollision(id, relativePosition);
			if (chekResult == true)
			{
				positionCollision = collisionPosition::right;
			}
			break;
		case 2:
			relativePosition.x = positionChek.x + (rect.w / 2);
			relativePosition.y = positionChek.y + rect.h;
			chekResult = checkIfCollision(id, relativePosition);
			if (chekResult == true&& positionCollision == collisionPosition::right)
			{
				positionCollision = collisionPosition::downAndRight;
			}
			else if(chekResult == true) 
			{
				positionCollision = collisionPosition::down;
			}
			else if (positionCollision == collisionPosition::right)
			{
				positionCollision = collisionPosition::right;
			}
			else 
			{
				positionCollision = collisionPosition::null;
			}
			break;
		case 3:
			relativePosition.x = positionChek.x;
			relativePosition.y = positionChek.y + (rect.h / 2);
			chekResult = checkIfCollision(id, relativePosition);
			if (chekResult == true && positionCollision == collisionPosition::down)
			{
				positionCollision = collisionPosition::downAndLeft;
			}
			else if(chekResult == true)
			{
				positionCollision = collisionPosition::left;
			}
			else if(positionCollision == collisionPosition::down)
			{
				positionCollision = collisionPosition::down;
			}
			else if(positionCollision == collisionPosition::right)
			{
				positionCollision = collisionPosition::right;
			}
			else 
			{
				positionCollision = collisionPosition::null;
			}
			break;
		}
	}
	
	return positionCollision;
}
bool collisions::checkIfCollision(int id, position positionToChek)
{
	bool result = false;
	int idChek;
	position numTilesMap;
	position tilePosition;
	/*numTilesMap.x = app->map->data.tilesets.start->data->numTilesWidth * app->map->data.tilesets.start->data->tileWidth;
	numTilesMap.y = app->map->data.tilesets.start->data->numTilesHeight * app->map->data.tilesets.start->data->tileHeight;*/
	numTilesMap.x = app->map->data.tilesets.start->data->tileWidth;
	numTilesMap.y = app->map->data.tilesets.start->data->tileHeight;
	tilePosition.x = positionToChek.x /numTilesMap.x ;
	tilePosition.y = positionToChek.y /numTilesMap.y ;
	ListItem<MapLayer*>* list1;
	
	for (list1 = app->map->data.layers.start; list1 != nullptr; list1=list1->next) 
	{
		if (list1->data->name == "colisions") 
		{
			idChek=list1->data->Get(tilePosition.x, tilePosition.y);

			if (idChek == id) 
			{
				result = true;
				return result;
			}
		}
	}
	return result;
}
// Called each loop iteration
bool Scene::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		app->map->ChangeCollisionsDraw();
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
		

	if (freeCamera==true)
	{
		if ((app->render->camera.x <= 0) && (app->render->camera.x >= -2920))
		{
			app->render->camera.x--;
		}
		if (((app->render->camera.y <= -700) && (app->render->camera.y >= -1055)) && (app->render->camera.x == -2921))
		{
			app->render->camera.y--;
		}
		if (((app->render->camera.y == -1056) && (app->render->camera.x <= -2921)) && (app->render->camera.x >= -5121))
		{
			app->render->camera.x--;
		}
		if ((app->render->camera.x <= -5122 && app->render->camera.x >= -5857) && (app->render->camera.y >= -1057 && app->render->camera.y <= -781))
		{
			app->render->camera.x--;
		}
		if ((app->render->camera.x <= -5622 && app->render->camera.x >= -5857) && (app->render->camera.y >= -1057 && app->render->camera.y <= -781))
		{
			app->render->camera.y++;
		}
		if (app->render->camera.x <= -5858 && app->render->camera.x >= -9000)
		{
			app->render->camera.x--;
		}
		if (app->render->camera.y >= -820 && app->render->camera.y <= -420 && app->render->camera.x <= -8000 && app->render->camera.x >= -9000)
		{
			app->render->camera.y++;
		}
	}
	else
	{
		if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			app->render->camera.y += 5;

		if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			app->render->camera.y -= 5;

		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			app->render->camera.x += 5;

		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			app->render->camera.x -= 5;
	}
	//DRAW BACKGROUND
	app->render->DrawTexture(bg_snow, 0, 0);
	app->render->DrawTexture(bg_snow, 3600, 0);
	app->render->DrawTexture(bg_snow, 7200, 0);



	app->map->Draw();
	// L03: DONE 7: Set the window title with map/tileset info
	
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->data.width, app->map->data.height,
		app->map->data.tileWidth, app->map->data.tileHeight,
		app->map->data.tilesets.count());

	app->win->SetTitle(title.GetString());
	//LOG("Position x: %d ------ Position y: %d", app->render->camera.x, app->render->camera.y);

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

	return true;
}

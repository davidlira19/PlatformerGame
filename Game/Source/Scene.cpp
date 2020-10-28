#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
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
	app->audio->PlayMusic("Assets/audio/music/Christmas_music2004.ogg");
	//Load Position
	app->render->camera.x = 0;
	app->render->camera.y = -700;
	//Load Texture
	bg_snow = app->tex->Load("Assets/textures/snow_background.png");

	freeCamera = true;
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		app->map->ChangeCollisionsDraw();
	}
	//CAMERA.X LIMITS
	if (app->render->camera.x > 0)
	{
		app->render->camera.x = 0;
	}
	else if (app->render->camera.x <= -9000)
	{
		app->render->camera.x = -9000;
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
	LOG("Position x: %d ------ Position y: %d", app->render->camera.x, app->render->camera.y);

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

#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "Map.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"
#include "Fonts.h"
#include "Collisions.h"
#include "FadeToBlack.h"
#include "EntityManager.h"
#include "PathFinding.h"
#include "GuiButton.h"
#include "GuiManager.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{
	name.Create("scene");
}

// Destructor
SceneLevel1::~SceneLevel1() {}

// Called before render is available
bool SceneLevel1::Awake()
{
	LOG("Loading Scene");
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool SceneLevel1::Start(bool newGame)
{
	menu = false;
	//app->audio->Enable();
	app->gui->Enable();
	app->collisions->Enable();
	app->entity->Enable();
	contMenu = 0;
	if (newGame == true)
	{
		app->LoadGameRequest("save_game.xml");
		app->player->isEnabled = true;
		app->player->Start(true);
	}
	else 
	{
		app->player->Enable();
		app->render->camera.x = -580;
		app->render->camera.y = -250;
		app->player->currentLevel = 1;

		//Player position
		app->player->position.x = 1150;
		app->player->position.y = 560;

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
	}
	// Load map
	app->map->Enable();
	app->map->Load("snow_tileset.tmx");

	// Load music
	
	app->audio->PlayMusic("Assets/Audio/Music/christmas_music.ogg");

	//Load Position
	

	//Load Texture
	bgSnow = app->tex->Load("Assets/Textures/snow_background.png");
	freeCamera = false;
	
	

	SDL_Rect rect;

	for (int y = 0; y < app->map->data.tilesets.start->data->numTilesHeight; y++)
	{
		for (int x =0 ; x < app->map->data.tilesets.start->data->numTilesWidth; x++)
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
				colliders.Add(app->collisions->AddCollider(rect, Collider::CHECKPOINT,(Module*)app->player));
			}
		}
	}

	//BIRDS
	

	char lookupTable[] = { "0123456789" };
	numbers = app->fonts->Load("Assets/Textures/numbers.png", lookupTable, 1);
	
	return true;
}

// Called each loop iteration
bool SceneLevel1::PreUpdate()
{
	ListItem<Collider*>* auxiliar;
	auxiliar = colliders.start;
	for (int y = 0; y < app->map->data.tilesets.start->data->numTilesHeight; y++)
	{
		for (int x = 0; x < app->map->data.tilesets.start->data->numTilesWidth; x++)
		{
			
			if ((app->map->GetTileIdFromPosition(x, y, "collisions") == 61 || app->map->GetTileIdFromPosition(x, y, "collisions") == 62) || app->map->GetTileIdFromPosition(x, y, "collisions") == 63 && auxiliar!=NULL)
			{		
				auxiliar->data->SetPos(x * app->map->data.tilesets.start->data->tileWidth + app->render->camera.x, y * app->map->data.tilesets.start->data->tileHeight + app->render->camera.y);
				auxiliar = auxiliar->next;
			}
		}
	}

	return true;
}

// Called each loop iteration
bool SceneLevel1::Update(float dt)
{
	if (menu == false)
	{
		frames++;
		if (app->vsync == false)
		{
			if (frames % 60 == 0)
			{
				timerLvl1--;
			}
		}
		else
		{
			if (frames % 30 == 0)
			{
				timerLvl1--;
			}
		}
		if (timerLvl1 == 0)
		{
			frames = 0;
			timerLvl1 = 99;
			app->player->lifes--;
			app->player->dead = true;
		}
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
			app->render->camera.x -= 500 * (dt / 1000);
	}

	//DRAW BACKGROUND
	app->render->DrawTexture(bgSnow, -3600 / 2, 0);
	app->render->DrawTexture(bgSnow, 0, 0);
	app->render->DrawTexture(bgSnow, 3600 / 2, 0);
	app->render->DrawTexture(bgSnow, 7200 / 2, 0);
	app->render->DrawTexture(bgSnow, 10800 / 2, 0);
	app->map->Draw();

	//CONDITIONS TO WIN - LOSE
	if (app->player->position.y >= 1602 / 2)
	{
		app->player->dead = true;
		app->player->lifes--;
		timerLvl1 = 99;
		frames = 0;
	}
	if (app->player->position.x >= 11350 / 2)
	{
		app->player->win = true;
	}

	if (menu == true && contMenu == 0)
	{
		contMenu++;
		
		app->player->godMode = true;
		app->player->canMove = false;

		SDL_Rect rect = { app->player->position.x - 500 + 500,app->player->position.y - 250 + 200,200,81 };
		resume = app->gui->CreateGuiControl(GuiControlType::BUTTON, 6, rect, "RESUME");
		resume->SetObserver(this);

		SDL_Rect rect2 = { app->player->position.x - 500 + 500,app->player->position.y - 250 + 300,200,81 };
		settings = app->gui->CreateGuiControl(GuiControlType::BUTTON, 3, rect2, "SETTINGS");
		settings->SetObserver(this);

		SDL_Rect rect3 = { app->player->position.x - 500 + 500,app->player->position.y - 250 + 400,200,81 };
		title = app->gui->CreateGuiControl(GuiControlType::BUTTON, 7, rect3, "TITLE");
		title->SetObserver(this);

		SDL_Rect rect4 = { app->player->position.x - 500 + 500,app->player->position.y - 250 + 500,200,81 };
		exit = app->gui->CreateGuiControl(GuiControlType::BUTTON, 5, rect4, "EXIT");
		exit->SetObserver(this);
	}
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		if ((menu == false) && ((app->player->currentAnimation != &app->player->jumpLeft) && (app->player->currentAnimation != &app->player->jumpRight)))
		{
			app->gui->pausedAnimationIn.Reset();
			app->audio->PlayFx(app->gui->menuEfect);
			menu = true;
			contMenu = 0;
		}
		else
		{
			app->gui->pausedAnimationOut.Reset();
			app->gui->outAnimation = true;
			app->audio->PlayFx(app->gui->menuEfect);
			app->gui->DestroyAllGuiControl();
			menu = false;
			app->player->godMode = false;
			app->player->canMove = true;
		}
	}


	return true;
}

// Called each loop iteration
bool SceneLevel1::PostUpdate()
{
	bool ret = true;
	
	score = app->player->points;

	sprintf_s(scoreText, 10, "%5d", score);
	app->fonts->BlitText((app->render->camera.x) * -1, (app->render->camera.y - 75) * -1, numbers, scoreText);

	sprintf_s(timerText, 10, "%2d", timerLvl1);
	app->fonts->BlitText((app->render->camera.x - 5) * -1, (app->render->camera.y - 150) * -1, numbers, timerText);

	return ret;
}

bool SceneLevel1::OnGuiMouseClickEvent(GuiControl* control)
{
	if (control == resume)
	{
		app->audio->PlayFx(app->gui->menuEfect);
		app->gui->pausedAnimationOut.Reset();
		app->gui->outAnimation = true;
		app->gui->DestroyAllGuiControl();
		menu = false;
		app->player->godMode = false;
		app->player->canMove = true;
	}else if (control == settings)
	{
		SDL_Rect rect = { app->player->position.x - 500 + 725,app->player->position.y - 250 + 400,91,96 };
		fullscreen = app->gui->CreateGuiControl(GuiControlType::CHECKBOX, 8, rect, "FULLSCREEN");
		fullscreen->SetObserver(this);

		rect = { app->player->position.x - 500 + 725,app->player->position.y - 250 + 500,91,96 };
		vsync = app->gui->CreateGuiControl(GuiControlType::CHECKBOX, 9, rect, "VSYNC");
		vsync->SetObserver(this);

		rect = { app->player->position.x - 500 + 825,app->player->position.y - 250 + 200,359,57 };
		musicVolume = app->gui->CreateGuiControl(GuiControlType::SLIDER, 1, rect, "MUSIC");
		musicVolume->SetObserver(this);

		rect = { app->player->position.x - 500 + 825,app->player->position.y - 250 + 300,359,57 };
		fxVolume = app->gui->CreateGuiControl(GuiControlType::SLIDER, 2, rect, "FX");
		fxVolume->SetObserver(this);
	}else if (control == fullscreen)	
	{
		if (app->win->fullScreenWindow == true)
		{
			app->win->fullScreenWindow = false;
		}
		else
		{
			app->win->fullScreenWindow = true;
		}
	}else if (control == vsync)	
	{
		if (app->maxFPS == 13)
		{
			app->maxFPS = 30;
			app->vsync = true;
		}
		else if (app->maxFPS == 30)
		{
			app->maxFPS = 13;
			app->vsync = false;
		}
	}else if (control == musicVolume)	
	{
		app->audio->volumeMusic = musicVolume->GetMusicValue();

	}else if (control == fxVolume)
	{
		app->audio->volumeFx = fxVolume->GetMusicValue();
	}else if (control == title)
	{
		//app->player->Disable();
		/*app->entity->Disable();*/
		app->gui->outAnimation = false;
		menu = false;
		app->gui->DestroyAllGuiControl();
		app->fade->FadeToBlack(this, (Module*)app->welcome, 60);
	}else if (control == exit)	
	{
		//app->SaveGame();
		SDL_Quit();
	}

	return true;
}

// Called before quitting
bool SceneLevel1::CleanUp()
{
	LOG("Freeing scene");
	app->fonts->UnLoad(numbers);
	app->render->camera.x = 0;
	app->render->camera.y = 0;
	app->tex->UnLoad(bgSnow);
	app->map->Disable();
	app->entity->Disable();
	app->player->Disable();
	//app->audio->Unload();
	app->gui->Disable();
	app->collisions->Disable();
	colliders.Clear();
	
	//app->audio->Disable();
	
	return true;
}
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

SceneLevel2::SceneLevel2(bool startEnabled) : Module(startEnabled)
{
	name.Create("scene2");
}

// Destructor
SceneLevel2::~SceneLevel2() {}

// Called before render is available
bool SceneLevel2::Awake()
{
	LOG("Loading Scene2");
	bool ret = true;
	
	return ret;
}

// Called before the first frame
bool SceneLevel2::Start(bool newGame)
{
	contMenu = 0;
	menu = false;
	app->gui->Enable();
	app->entity->Enable();
	app->collisions->Enable();
	if (newGame == true)
	{
		app->LoadGameRequest("save_game.xml");
		app->player->isEnabled = true;
		app->player->Start(true);
	}
	else 
	{
		app->player->Enable();
		app->render->camera.x = 0;
		app->render->camera.y = 0;
		app->player->currentLevel = 2;

		//Player position
		app->player->position.x = 600;
		app->player->position.y = 330;


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
	}

	app->map->Enable();
	app->map->Load("snow_tileset_lvl2.tmx");

	
	app->audio->PlayMusic("Assets/Audio/Music/christmas_music.ogg");

	//Load Position
	

	//Load Texture
	mysteryTex = app->tex->Load("Assets/Textures/mystery.png");
	screamFx = app->audio->LoadFx("Assets/Audio/Fx/scream.wav");
	bgSnow = app->tex->Load("Assets/Textures/snow_background.png");
	coin = app->tex->Load("Assets/Textures/coin_animation.png");
	watch = app->tex->Load("Assets/Textures/watch.png");
	freeCamera = false;
	
	
	
	counter = 1000;
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
	

	char lookupTable[] = { "0123456789" };
	numbers = app->fonts->Load("Assets/Textures/numbers.png", lookupTable, 1);

	return true;
}

// Called each loop iteration
bool SceneLevel2::PreUpdate()
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
bool SceneLevel2::Update(float dt)
{
	if (menu == false)
	{
		frames++;
		if (app->vsync == false)
		{
			if (frames % 60 == 0)
			{
				timerLvl2--;
			}
		}
		else
		{
			if (frames % 30 == 0)
			{
				timerLvl2--;
			}
		}
		if (timerLvl2 == 0)
		{
			frames = 0;
			timerLvl2 = 99;
			app->player->lifes--;
			app->player->dead = true;
		}
	}
	
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
	app->render->DrawTexture(bgSnow, -3600 / 2, 0);
	app->render->DrawTexture(bgSnow, 0, 0);
	app->render->DrawTexture(bgSnow, 3600 / 2, 0);
	app->render->DrawTexture(bgSnow, 7200 / 2, 0);
	app->render->DrawTexture(bgSnow, 10800 / 2, 0);
	app->render->DrawTexture(bgSnow, -3600 / 2, 893);
	app->render->DrawTexture(bgSnow, 0, 893);
	app->render->DrawTexture(bgSnow, 3600 / 2, 893);
	app->render->DrawTexture(bgSnow, 7200 / 2, 893);
	app->render->DrawTexture(bgSnow, 10800 / 2, 893);
	app->map->Draw();

	if (app->player->position.y >= 1310)
	{
		app->player->dead = true;
		app->player->lifes--;
		timerLvl2 = 99;
		frames = 0;
	}
	if (app->player->position.x >= 6726)
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

	SDL_Rect rect = { 2,2,41,41 };
	app->render->DrawTexture(coin, app->render->camera.x * -1 + 175, app->render->camera.y * -1 + 80, &rect);
	app->render->DrawTexture(watch, app->render->camera.x * -1 + 75, app->render->camera.y * -1 + 155);
	return true;
}

// Called each loop iteration
bool SceneLevel2::PostUpdate()
{
	bool ret = true;

	score = app->player->points;

	sprintf_s(scoreText, 10, "%5d", score);
	app->fonts->BlitText((app->render->camera.x) * -1, (app->render->camera.y - 75) * -1, numbers, scoreText);

	sprintf_s(timerText, 10, "%2d", timerLvl2);
	app->fonts->BlitText((app->render->camera.x - 5) * -1, (app->render->camera.y - 150) * -1, numbers, timerText);

	if (app->player->points == 1750 && counter >= 0)
	{
		EasterEgg();
		counter -= 10;
	}
	if (counter == 0)
	{
		app->player->points += 5000;
		counter = -1;
	}
	return ret;
}

bool SceneLevel2::OnGuiMouseClickEvent(GuiControl* control)
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
		app->gui->outAnimation = false;
		menu = false;
		app->gui->DestroyAllGuiControl();
		app->fade->FadeToBlack(this, (Module*)app->welcome, 60);
	}else if (control == exit)	
	{
		SDL_Quit();
	}

	return true;
}

void SceneLevel2::EasterEgg()
{
	if (counter == 1000)
	{
		app->audio->PlayFx(screamFx);
	}
	app->render->DrawTexture(mysteryTex, ((app->render->camera.x - 300) * -1), (app->render->camera.y * -1));
}

// Called before quitting
bool SceneLevel2::CleanUp()
{
	LOG("Freeing scene");
	app->fonts->UnLoad(numbers);
	app->render->camera.x = 0;
	app->render->camera.y = 0;
	app->tex->UnLoad(bgSnow);
	app->tex->UnLoad(mysteryTex);
	app->tex->UnLoad(watch);
	app->audio->Unload(screamFx);
	app->map->Disable();
	app->entity->Disable();
	
	//app->audio->Unload();
	//app->gui->Disable();
	app->gui->DestroyAllGuiControl();
	app->collisions->Disable();
	ListItem<Collider*>* auxiliar;
	auxiliar = colliders.start;
	while (auxiliar != nullptr)
	{
		colliders.Del(auxiliar);
		auxiliar = auxiliar->next;
	}
	
	return true;
}
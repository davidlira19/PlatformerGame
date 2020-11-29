#include "App.h"
#include "Input.h"
#include "Window.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Player.h"
#include "Enemies.h"
#include "Scene.h"
#include"Intro.h"
#include "Map.h"
#include"FadeToBlack.h"
#include "Defs.h"
#include "Log.h"
#include"Wellcome.h"
#include"Dead.h"
#include"Win.h"
#include"Collisions.h"
#include <iostream>
#include <sstream>

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	frames = 0;
	PERF_START(ptimer);

	input = new Input(true);
	win = new Window(true);
	render = new Render(true);
	tex = new Textures(true);
	audio = new Audio(true);
	player = new Player(false);
	enemy = new Enemy(false);
	scene = new Scene(false);
	map = new Map(false);
	fade = new ModuleFadeToBlack(true);
	intro = new Intro(true);
	wellcome= new Wellcome(false);
	dead = new Dead(false);
	winp = new Win(false);
	collisions = new ModuleCollisions(true);
	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	
	AddModule(intro);
	AddModule(wellcome);
	AddModule(dead);
	AddModule(winp);
	AddModule(fade);	
	AddModule(player);
	AddModule(enemy);
	AddModule(scene);
	AddModule(map);
	AddModule(collisions);
	// Render last to swap buffer
	AddModule(render);

	PERF_PEEK(ptimer);
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.Clear();

	configFile.reset();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.Add(module);
}

// Called before render is available
bool App::Awake()
{
	PERF_START(ptimer);
	
	// TODO 3: Load config from XML
	bool ret = LoadConfig();

	// TODO 4: Read the title from the config file
	title.Create(configApp.child("title").child_value());
	win->SetTitle(title.GetString());

	if(ret == true)
	{
		ListItem<Module*>* item;
		item = modules.start;

		while(item != NULL && ret == true)
		{
			// TODO 5: Add a new argument to the Awake method to receive a pointer to an xml node.
			// If the section with the module name exists in config.xml, fill the pointer with the valid xml_node
			// that can be used to read all variables for that module.
			// Send nullptr if the node does not exist in config.xml
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called before the first frame
bool App::Start()
{
	PERF_START(ptimer);

	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{
		if (item->data->isEnabled == true) 
		{
			ret = item->data->Start();
		}
		item = item->next;
		
		
	}

	PERF_PEEK(ptimer);

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// Load config from XML file
bool App::LoadConfig()
{
	bool ret = true;

	// TODO 3: Load config.xml file using load_file() method from the xml_document class
	pugi::xml_parse_result result = configFile.load_file("config.xml");

	// TODO 3: Check result for loading errors
	if(result == NULL)
	{
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		config = configFile.child("config");
		configApp = config.child("app");
	}

	return ret;
}

// ---------------------------------------------
void App::PrepareUpdate()
{
}

// ---------------------------------------------
void App::FinishUpdate()
{
	// L02: DONE 1: This is a good place to call Load / Save methods
	if (loadGameRequested == true) LoadGame();
	if (saveGameRequested == true) SaveGame();

	// L07: DONE 4: Now calculate:
	// Amount of frames since startup
	// Amount of time since game start (use a low resolution timer)
	// Average FPS for the whole game life
	// Amount of ms took the last update
	// Amount of frames during the last second
	if (lastSecFrameTime.Read() > 1000)
	{
		lastSecFrameTime.Start();
		prevLastSecFrameCount = lastSecFrameCount;
		lastSecFrameCount = 0;
	}

	float averageFps = float(frameCount) / startupTime.ReadSec();
	float secondsSinceStartup = startupTime.ReadSec();
	uint lastFrameMs = frameTime.Read();
	uint framesOnLastUpdate = prevLastSecFrameCount;

	static char title[256];
	sprintf_s(title, 256, "Av.FPS: %.2f Last Frame Ms: %02u Last sec frames: %i Last dt: %.3f Time since startup: %.3f Frame Count: %I64u ",
		averageFps, lastFrameMs, framesOnLastUpdate, dt, secondsSinceStartup, frameCount);

	app->win->SetTitle(title);
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->isEnabled == false)
		{
			continue;
		}

		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->isEnabled == false)
		{
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		
		pModule = item->data;

		if(pModule->isEnabled == false) 
		{
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

// ---------------------------------------
int App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* App::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save
// L02: TODO 7: Implement the xml save method for current state
void App::LoadGameRequest(const char* name)
{
	// NOTE: We should check if SAVE_STATE_FILENAME actually exist
	loadGameRequested = true;
	loadedGame.Create("save_game.xml");
	
}

// ---------------------------------------
void App::SaveGameRequest(const char* name) const
{
	// NOTE: We should check if SAVE_STATE_FILENAME actually exist and... should we overwriten
	saveGameRequested = true;
	/*if (savedGame != loadedGame)
	{
		
	}*/
	
	
}
// L02: TODO 5: Create a method to actually load an xml file
// then call all the modules to load themselves
void App::LoadGame() 
{
	ListItem<Module*>* item = nullptr;
	pugi::xml_document LoadFile;
	pugi::xml_node load;
	LoadFile.load_file(loadedGame.GetString());
	load = LoadFile.child("game_state");

	for (item = modules.start; item != nullptr; item = item->next) 
	{
		item->data->LoadState(&load.child(item->data->name.GetString()));
	}
	loadGameRequested = false;
}
void App::SaveGame() 
{
	
	pugi::xml_document SaveFile;
	//pugi::xml_node Save;
	auto Save = SaveFile.append_child("game_state");
	ListItem<Module*>* item = nullptr;

	for (item = modules.start; item != nullptr; item = item->next) 
	{
		Save.append_child(item->data->name.GetString());
		item->data->SaveState(&Save.child(item->data->name.GetString()));
	}
	SaveFile.save_file("save_game.xml");
	saveGameRequested = false;
}
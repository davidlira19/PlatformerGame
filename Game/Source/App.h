#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "PerfTimer.h"
#include "Timer.h"
#include "List.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Player;
class EntityManager;
class SceneLevel1;
class SceneLevel2;
class Map;
class ModuleFadeToBlack;
class Intro;
class Wellcome;
class Dead;
class Win;
class Fonts;
class ModuleCollisions;
class GuiManager;
class App
{
public:
	void LoadGame();
	void SaveGame();

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	//Create methods to request Load / Save
	void LoadGameRequest(const char* name);
	void SaveGameRequest(const char* name) const;

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Player* player;
	EntityManager* entity;
	SceneLevel1* sceneLevel1;
	SceneLevel2* sceneLevel2;
	Map* map;
	ModuleFadeToBlack* fade;
	Intro* intro;
	Wellcome* wellcome;
	Dead* dead;
	Win* winp;
	Fonts* fonts;
	ModuleCollisions* collisions;
	GuiManager* gui;
private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;

	// Create new variables from pugui namespace:
	// a xml_document to store the config file and
	// two xml_node to read specific branches of the xml
	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	uint frames;

	mutable bool saveGameRequested;
	bool loadGameRequested;
	SString loadedGame;
	SString savedGame;

	// Calculate some timing measures required variables are provided:
	PerfTimer ptimer;
	PerfTimer dif;

	uint frameCount = 0;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;
	uint lastSecFrameCount = 0;
	uint prevLastSecFrameCount = 0;
	float dt = 0.0f;

	int	cappedMs = -1;

	int maxFPS;

public:
	bool vsync;
};

extern App* app;

#endif	// __APP_H__
#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include "Module.h"
#include "GuiControl.h"
#include"Animation.h"
#include "List.h"

class GuiManager : public Module
{
public:

	GuiManager(bool startEnabled);

	// Destructor
	virtual ~GuiManager();

	// Called before render is available
	

	//// Called before the first frame
	

	//// Called before quitting
	
	// Additional methods
	GuiControl* CreateGuiControl(GuiControlType type,int id,SDL_Rect rect,const char* text);
	bool Update(float dt);
	bool CleanUp();
	void DestroyGuiControl(GuiControl* entity);
	void DestroyAllGuiControl();
	//bool Start();
	bool PostUpdate();
	bool Start(bool newGame);
	//void AddGuiControl(GuiControl* entity);
	//bool Awake(pugi::xml_node&);
public:
	SDL_Texture* textureButton;
	SDL_Texture* textureSlider;
	List<GuiControl*> controls;
	Animation pausedAnimation;
	unsigned int focusedFx;
	unsigned int clickedFx;
	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;
};

#endif // __GUIMANAGER_H__

#ifndef __SCENE2_H__
#define __SCENE2_H__

#include "Module.h"

struct SDL_Texture;
class position;

class SceneLevel2 : public Module
{
public:

	SceneLevel2(bool startEnabled);

	// Destructor
	virtual ~SceneLevel2();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start(bool newGame);

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

	bool freeCamera;

private:

	void EasterEgg();

	int counter;
	uint score = 000000;
	int numbers = -1;
	char scoreText[5] = { "\0" };
	char timerText[2] = { "\0" };
	unsigned int screamFx;
	List<Collider*> colliders;
	SDL_Texture* img;
	SDL_Texture* bgSnow;
	SDL_Texture* mysteryTex;
	bool menu = false;
	int contMenu = 0;
	GuiControl* resume;
	GuiControl* exit;
	GuiControl* title;
	GuiControl* settings;
public:
	uint frames = 0;
	uint timerLvl2 = 99;
};

#endif // __SCENE_H__
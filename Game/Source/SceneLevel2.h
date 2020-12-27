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
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool freeCamera;

private:

	void EasterEgg();

	int counter;
	uint score = 000000;
	int numbers = -1;
	char scoreText[5] = { "\0" };
	char timerText[3] = { "\0" };
	unsigned int screamFx;
	List<Collider*> colliders;
	SDL_Texture* img;
	SDL_Texture* bgSnow;
	SDL_Texture* mysteryTex;
public:
	uint frames = 0;
	uint timerLvl2 = 100;
};

#endif // __SCENE_H__
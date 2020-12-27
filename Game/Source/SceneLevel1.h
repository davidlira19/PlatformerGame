#ifndef __SCENELEVEL1_H__
#define __SCENELEVEL1_H__

#include "Module.h"

struct SDL_Texture;
class position;

class collisions
{
public:

	collisionPosition getCollision(position positionChek,SDL_Rect rect,int id);
	bool checkIfCollision(int id, position positionToChek);
};

class SceneLevel1 : public Module
{
public:

	SceneLevel1(bool startEnabled);

	// Destructor
	virtual ~SceneLevel1();

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
	uint score = 000000;
	int numbers = -1;
	char scoreText[5] = { "\0" };
	char timerText[3] = { "\0" };

	List<Collider*> colliders;
	SDL_Texture* img;
	SDL_Texture* bgSnow;
public:
	uint frames = 0;
	uint timerLvl1 = 100;
};

#endif // __SCENELEVEL1_H__
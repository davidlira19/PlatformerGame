#ifndef __SCENE2_H__
#define __SCENE2_H__

#include "Module.h"

struct SDL_Texture;
class position;

class Scene2 : public Module
{
public:

	Scene2(bool startEnabled);

	// Destructor
	virtual ~Scene2();

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

	List<Collider*> colliders;
	SDL_Texture* img;
	SDL_Texture* bgSnow;
};

#endif // __SCENE_H__
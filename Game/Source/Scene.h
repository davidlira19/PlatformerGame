#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

struct SDL_Texture;
class position;

class collisions 
{
public:
	collisionPosition getCollision(position positionChek,SDL_Rect rect,int id);
	bool checkIfCollision(int id, position positionToChek);
};
class Scene : public Module
{
public:

	Scene(bool startEnabled);

	// Destructor
	virtual ~Scene();

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
	List<Collider*>colliders;
	SDL_Texture* img;
	SDL_Texture* bg_snow;
};

#endif // __SCENE_H__
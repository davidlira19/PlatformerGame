#ifndef _PLAYER_H_
#define _PLAYER_H_
#include"App.h"
#include"Render.h"
#include"Textures.h"
#include"Animation.h"
#include"Module.h"
#include "Scene.h"
struct SDL_Rect;
struct SDL_Texture;
struct SDL_Renderer;
class position
{
public:
	int x, y;
};
class Player : public Module
{
public:
	Player(bool startEnabled);
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void updatePosition();
	//PLAYER VARIABLES
	bool isJumping;
	//PLAYER FUNCTIONS
	void JumpFunction();
	//PLAYER POSITION
	position Position;
	//PLAYER ANIMATIONS
	Animation* lastanimation = nullptr;
	Animation* currentAnimation = nullptr;

	Animation StopRight;
	Animation JumpRight;
	Animation RunRight;
	Animation DeadRight;
	SDL_Rect collider;
	Animation StopLeft;
	Animation JumpLeft;
	Animation RunLeft;
	Animation DeadLeft;
	collisions playerCollisions;
private:
	//PLAYER TEXTURE
	SDL_Texture* santa = nullptr;

};
#endif


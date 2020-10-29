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
enum class  playerState
{
	null, jumping
};
class position
{
public:
	int x, y;
};
class Player : public Module
{
public:
	playerState state;
	void Gravity();
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
	float aceleration, velocity;
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
	int jumpingCount;
	bool godMode;
private:
	//PLAYER TEXTURE
	SDL_Texture* santa = nullptr;

};
#endif


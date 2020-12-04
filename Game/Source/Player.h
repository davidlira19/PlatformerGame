#ifndef _PLAYER_H_
#define _PLAYER_H_
#include"App.h"
#include"Render.h"
#include"Textures.h"
#include"Animation.h"
#include"Module.h"
#include "Scene.h"
#include "Scene2.h"
struct SDL_Rect;
struct SDL_Texture;
struct SDL_Renderer;
enum class  playerState
{
	null, jumping,free
};
class position
{
public:
	int x, y;
};
class Player : public Module
{
public:
	bool HasThePlayerMove();
	playerState state;
	void Gravity(float dt);
	Player(bool startEnabled);
	bool Start();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void updatePosition();
	//PLAYER VARIABLES
	int lifes;
	bool isJumping;
	int points;
	int maxPoints;
	int currentLevel;
	//PLAYER FUNCTIONS
	void JumpFunction(float dt);
	void DeadAction();
	//PLAYER POSITION
	position Position,lastPosition;
	collisionPosition result;
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
	bool canMove;
	bool Intro;
	bool LoadState(pugi::xml_node* nodo);
	bool SaveState(pugi::xml_node* nodo);
	// WIN-LOSE TEXTURES
	SDL_Texture* WinTex = nullptr;
	SDL_Texture* DeadTex = nullptr;
	SDL_Texture* IntroTex = nullptr;
	//FX AUDIO
	unsigned int jumpFx;
	unsigned int landFx;
	unsigned int coinFx;
	unsigned int lifeFx;
	unsigned int checkpointFx;
	bool lateralsR;
	bool lateralsL;
	// WIN-LOSE BOOLS
	bool Win;
	bool Dead;
	Collider* playerDown;
	Collider* playerRight;
	Collider* playerLeft;
	void OnCollision(Collider* c1, Collider* c2);
	iPoint GetPosition();
private:
	//PLAYER TEXTURE

	int cont;
	bool noise;
	SDL_Texture* santa = nullptr;
	SDL_Texture* LifesTex = nullptr;
};
#endif


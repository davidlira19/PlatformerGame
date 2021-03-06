#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"App.h"
#include"Render.h"
#include"Textures.h"
#include"Animation.h"
#include"Module.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"

struct SDL_Rect;
struct SDL_Texture;
struct SDL_Renderer;

enum class  playerState
{
	null, jumping, free
};

class position
{
public:
	~position(){}
	int x, y;
};

class Player : public Module
{
public:

	bool HasThePlayerMove();
	playerState state;
	void Gravity(float dt);
	Player(bool startEnabled);
	~Player();
	bool Start(bool newGame);
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	//PLAYER VARIABLES
	int lifes;
	int points;
	bool isJumping;
	int currentLevel;

	//PLAYER FUNCTIONS
	void JumpFunction(float dt);
	void DeadAction();

	//PLAYER POSITION
	position position, lastPosition;
	collisionPosition result;

	//PLAYER ANIMATIONS
	Animation* lastanimation = nullptr;
	Animation* currentAnimation = nullptr;
	float acceleration, velocity;
	Animation stopRight;
	Animation jumpRight;
	Animation runRight;
	Animation deadRight;
	SDL_Rect collider;
	Animation stopLeft;
	Animation jumpLeft;
	Animation runLeft;
	Animation deadLeft;
	int jumpingCount;
	bool godMode;
	bool canMove;
	bool intro;
	bool LoadState(pugi::xml_node* nodo);
	bool SaveState(pugi::xml_node* nodo);
	bool LoadPL();
	bool SavePL();

	//FX AUDIO
	unsigned int jumpFx;
	unsigned int landFx;
	unsigned int coinFx;
	unsigned int lifeFx;
	unsigned int checkpointFx;
	bool lateralsR;
	bool lateralsL;

	// WIN-LOSE BOOLS
	bool win;
	bool dead;
	Collider* playerDown;
	Collider* playerRight;
	Collider* playerLeft;
	void OnCollision(Collider* c1, Collider* c2);

private:
	int pathCounter;
	//PLAYER TEXTURE
	int cont;
	bool noise;
	SDL_Texture* santa = nullptr;
	SDL_Texture* lifesTex = nullptr;
};
#endif
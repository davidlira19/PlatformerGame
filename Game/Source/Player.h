#ifndef _PLAYER_H_
#define _PLAYER_H_
#include"App.h"
#include"Render.h"
#include"Textures.h"
#include"Animation.h"
#include"Module.h"
struct SDL_Rect;
struct SDL_Texture;
struct SDL_Renderer;
class posicion
{
public:
	int x, y;
};
class Player : public Module
{
public:
	Player();
	virtual ~Player();
	bool Start();
	bool Update();
	bool PostUpdate();
	bool CleanUp();

private:
	SDL_Texture* santa = nullptr;

};
#endif


#ifndef __ENTITY_H__
#define __ENTITY_H__
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Collider.h"
#include "PathFinding.h"
#include "Render.h"
enum class EntityTipe
{
	NO_TYPE,
	EnemyAir,
	EnemyGround,
	Coin,
	Heart
};
class Entity
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Entity(int x, int y);

	// Destructor
	virtual ~Entity();
	// Returns the enemy's collider
	//const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	// Triggers an animation and a sound fx
	virtual void OnCollision(Collider* collideri, Collider* collidere);

public:
	int dire;
	void destr();
	// Current Position in the world
	iPoint position;
	bool pendientedeelim = false;
	// The enemy's texture
	EntityTipe type;
	// Sound fx when destroyed
	SDL_Texture* airEnemiesTexture;
	SDL_Texture* groundEnemiesTexture;
	SDL_Texture* moneyTexture;
	SDL_Texture* lifeTexture;
	Collider* playerWin = nullptr;
	// The enemy's collider
	Collider* collider = nullptr;
	PathFinding path;
	bool counter;
	int numCounter;
	bool deadZ;
	bool left;
	bool drawPath;
	unsigned int birdFx;
protected:

	// A ptr to the current animation
	Animation* currentAnim = nullptr;
	
	// Original spawn position
	iPoint spawnPos;
};

#endif // __ENTITY_H__*/

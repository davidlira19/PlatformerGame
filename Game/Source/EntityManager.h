#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include "Entity.h"
#include "Module.h"
#include "Enemy_Air.h"
#include "Enemy_Ground.h"
#include "Coin.h"
#include "Heart.h"
#include "List.h"
#include "Textures.h"

#define MAX_ENEMIES 100

struct EnemySpawnpoint
{
	EntityTipe type = EntityTipe::NO_TYPE;
	int x, y, direction;
};

class EntityManager : public Module
{
public:
	// Constructor
	EntityManager(bool startEnabled);
	bool PreUpdate();

	// Destructor
	~EntityManager();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start();

	// Called at the beginning of the application loop
	// Removes all enemies pending to delete

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	bool Update(float dt);

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	bool PostUpdate();

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp();

	// Called when an enemi collider hits another collider
	// The enemy is destroyed and an explosion particle is fired

	// Add an enemy into the queue to be spawned later
	bool AddEntity(EntityTipe type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandleEnemiesSpawn();
	void OnCollision(Collider* c1, Collider* c2);

	// Destroys any enemies that have moved outside the camera limits
	void HandleEnemiesDespawn();
	bool LoadState(pugi::xml_node* nodo);
	bool SaveState(pugi::xml_node* nodo);
	bool drawItems;
	List<Entity*>entityList;

private:
	// Spawns a new enemy using the data from the queue
	void SpawnEnemy(const EnemySpawnpoint& info);
	SDL_Texture* birdTexture;
	SDL_Texture* zombieTexture;
	SDL_Texture* coinTexture;
	SDL_Texture* heartTexture;
	int destroyedFx = 0;
	
	// A queue with all spawn points information
	EnemySpawnpoint spawnQueue[MAX_ENEMIES];
};

#endif // __ENTITYMANAGER_H__
#ifndef __MAP_H__
#define __MAP_H__

#include "Module.h"
#include "List.h"
#include "Point.h"

#include "PugiXml\src\pugixml.hpp"

// L03: DONE 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
struct TileSet
{
	SString	name;
	int	firstgid;
	int margin;
	int	spacing;
	int	tileWidth;
	int	tileHeight;
	int tile_width;
	int tile_height;
	SDL_Texture* texture;
	int	texWidth;
	int	texHeight;
	int	numTilesWidth;
	int	numTilesHeight;
	int	offsetX;
	int	offsetY;
	SDL_Rect GetTileRect(int id) const;
};

// L03: DONE 1: We create an enum for map type, just for convenience,
// NOTE: Platformer game will be of type ORTHOGONAL
enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

struct MapLayer
{
	SString	name;
	int width;
	int height;
	uint* data;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	// L04: DONE 6: Short function to get the value of x,y
	inline uint Get(int x, int y) const
	{
		return data[(y * width) + x];
	}
};

// L03: DONE 1: Create a struct needed to hold the information to Map node
struct MapData
{
	int width;
	int	height;
	int	tileWidth;
	int	tileHeight;
	SDL_Color backgroundColor;
	MapTypes type;
	List<TileSet*> tilesets;
	List<MapLayer*> layers;
};

class Map : public Module
{
public:

    Map();

    // Destructor
    virtual ~Map();

    // Called before render is available
    bool Awake(pugi::xml_node& conf);

    // Called each loop iteration
    void Draw();

    // Called before quitting
    bool CleanUp();

    // Load new map
    bool Load(const char* path);
	iPoint MapToWorld(int x, int y) const;

private:

	// L03: DONE Methods to load all required map data
	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	

public:
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);

    // L03: DONE 1: Add your struct for map info
	MapData data;

private:

    pugi::xml_document mapFile;
    SString folder;
    bool mapLoaded;
};

#endif // __MAP_H__
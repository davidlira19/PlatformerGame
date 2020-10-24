#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>

Map::Map() : Module(), mapLoaded(false)
{
    name.Create("map");
}

// Destructor
Map::~Map()
{}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    folder.Create(config.child("folder").child_value());

    return ret;
}

// Draw the map (all requried layers)
void Map::Draw()
{

}


// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

    // L03: DONE 2: Make sure you clean up any memory allocated from tilesets/map
    // Remove all tilesets
	ListItem<TileSet*>* item;
	item = data.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.clear();

	// Clean up the pugui tree
	mapFile.reset();

    return true;
}

// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

	// Load general info
    if(ret == true)
    {
        // L03: DONE 3: Create and call a private function to load and fill all your map data
		ret = LoadMap();
	}

    // L03: DONE 4: Create and call a private function to load a tileset
    // remember to support more any number of tilesets!
	pugi::xml_node tileset;
	for (tileset = mapFile.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if (ret == true) ret = LoadTilesetDetails(tileset, set);

		if (ret == true) ret = LoadTilesetImage(tileset, set);

		data.tilesets.add(set);
	}
    
    if(ret == true)
    {
        // L03: DONE 5: LOG all the data loaded iterate all tilesets and LOG everything
		ListItem<TileSet*>* list1;
		list1 = data.tilesets.start;

		LOG("Succesfully parsed map XML file: hello2.tmx",);
		LOG("width: %d tile_height: %d", data.width, data.height);
		LOG("tile_width: %d tile_heigh: %d", data.tileWidth, data.tileHeight);
    }

    mapLoaded = ret;

    return ret;
}

// L03: DONE: Load map general properties
bool Map::LoadMap()
{
	bool ret = true;
	pugi::xml_node map = mapFile.child("map");

	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tileWidth = map.attribute("tilewidth").as_int();
		data.tileHeight = map.attribute("tileheight").as_int();
	}

	return ret;
}

// L03: DONE: Load Tileset attributes
bool Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;

	if (tileset_node == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'tileset' tag.");
		ret = false;
	}
	else
	{
		set->firstgid = tileset_node.attribute("firstgrid").as_int();
		set->name = tileset_node.attribute("name").as_string();
		set->tileWidth = tileset_node.attribute("tileWidth").as_int();
		set->tileHeight = tileset_node.attribute("tileHeight").as_int();
		set->margin = tileset_node.attribute("margin").as_int();
		set->spacing = tileset_node.attribute("spacing").as_int();
	}

	return ret;
}

// L03: DONE: Load Tileset image
bool Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string("tmw_desert_spacing.png"));
		set->texture = app->tex->Load(tmp.GetString());
		set->texWidth = tileset_node.attribute("texWidth").as_int();
		set->texHeight = tileset_node.attribute("texHeight").as_int();
		set->numTilesWidth = tileset_node.attribute("numTilesWidth").as_int();
		set->numTilesHeight = tileset_node.attribute("numTilesHeight").as_int();
		set->offsetX = tileset_node.attribute("offsetX").as_int();
		set->offsetY = tileset_node.attribute("offsetY").as_int();
	}

	return ret;
}
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

// L06: TODO 7: Ask for the value of a custom property
int Properties::GetProperty(const char* value, int defaultValue) const
{
	//...

	return defaultValue;
}

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
	if (mapLoaded == false) return;

	// L04: DONE 5: Prepare the loop to draw all tilesets + DrawTexture()
	MapLayer* layer = data.layers.start->data;
	ListItem<TileSet*>* node;
	node = data.tilesets.start;
	// L06: TODO 4: Make sure we draw all the layers and not just the first one
	for (int y = 0; y < data.height; ++y)
	{
		for (int x = 0; x < data.width; ++x)
		{
			int tileId = layer->Get(x, y);
			if (tileId > 0)
			{
				iPoint point = MapToWorld(x, y);
				app->render->DrawTexture(node->data->texture, point.x, point.y, &node->data->GetTileRect(tileId));
				// L04: DONE 9: Complete the draw function
			}
		}
	}
}
iPoint Map::MapToWorld(int x, int y) const
{
	iPoint ret(0,0);

	// L05: DONE 1: Add isometric map to world coordinates
	if (data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * data.tileWidth;
		ret.y = y * data.tileHeight;
	}
	else if (data.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (data.tileWidth / 2);
		ret.y = (x + y) * (data.tileHeight / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

// L05: DONE 2: Add orthographic world to map coordinates
iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	// L05: DONE 3: Add the case for isometric maps to WorldToMap
	if (data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / data.tileWidth;
		ret.y = y / data.tileHeight;
	}
	else if (data.type == MAPTYPE_ISOMETRIC)
	{

		float half_width = data.tileWidth * 0.5f;
		float half_height = data.tileHeight * 0.5f;
		ret.x = int((x / half_width + y / half_height) / 2);
		ret.y = int((y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

// L06: TODO 3: Pick the right Tileset based on a tile id
TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* item = data.tilesets.start;
	TileSet* set = item->data;
	bool correct = false;

	while (correct == false)
	{
		if (id >= item->data->firstgid && id < item->next->data->firstgid)
		{
			set = item->data;
			correct = true;
		}
		else
		{
			item = item->next;
		}
	}

	return set;
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
SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	// L04: DONE 7: Get relative Tile rectangle
	int relativeId = id - firstgid;
	rect.w = tileWidth;
	rect.h = tileHeight;

	//ISOMETRIC
	int res = id / 4;
	int hond = id % 4;
	if (hond == 0) {
		hond = 4;
		res = res - 1;
	}
	hond = hond - 1;
	rect.x = hond * rect.w;
	rect.y = res * rect.h;

	//ORTHOGONAL
	/*int res = id / 8;
	int hond = id % 8;
	if (hond == 0) {
		hond = 8;
		res = res - 1;
	}
	hond = hond - 1;
	rect.x = margin * hond + hond * rect.w + margin;
	rect.y = margin * res + res * rect.h + margin;*/
	return rect;
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
	if (ret == true)
	{
		// L03: DONE 3: Create and call a private function to load and fill all your map data
		ret = LoadMap();
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
	pugi::xml_node layer;
	for (layer = mapFile.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* lay = new MapLayer();

		ret = LoadLayer(layer, lay);

		if (ret == true)
			data.layers.add(lay);
	}
    mapLoaded = ret;

    return ret;
}
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	layer->height = node.attribute("height").as_int();
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->data = new uint[750];
	memset(layer->data, 0, 750);
	pugi::xml_node node1 = node.child("data").child("tile");
	for (int i = 0; i < 750; i++) {
		layer->data[i] = node1.attribute("gid").as_int();
		node1 = node1.next_sibling("tile");
	}
	// L04: TODO 3: Load a single layer

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
		ListItem<TileSet*>* node;
		node = data.tilesets.start;
		// L03: TODO: Load map general properties
		data.tileHeight = map.attribute("tileheight").as_int(32);
		data.tileWidth = map.attribute("tilewidth").as_int(32);
		node->data->numTilesHeight = map.attribute("height").as_int();
		node->data->numTilesWidth = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.width = map.attribute("width").as_int();
		SString tmp("%s", map.attribute("orientation").value());
		if (tmp=="orthogonal")
		{
			data.type = MapTypes::MAPTYPE_ORTHOGONAL;
		}
		else if (tmp=="isometric")
		{
			data.type = MapTypes::MAPTYPE_ISOMETRIC;
		}
		else if (tmp == "staggered")
		{
			data.type = MapTypes::MAPTYPE_STAGGERED;
		}
		else
		{
			data.type = MapTypes::MAPTYPE_UNKNOWN;
		}
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
		set->firstgid = tileset_node.attribute("firstgid").as_int(1);
		set->margin = tileset_node.attribute("margin").as_int(1);
		set->name = tileset_node.attribute("name").as_string("Desert");
		set->tile_width = tileset_node.attribute("tilewidth").as_int(32);
		set->tile_height = tileset_node.attribute("tileheight").as_int(32);
		set->tileHeight = tileset_node.attribute("tileheight").as_int(32);
		set->tileWidth = tileset_node.attribute("tilewidth").as_int(32);
		set->spacing = tileset_node.attribute("spacing").as_int(1);
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
		set->texHeight = image.attribute("height").as_int(199);
		set->texWidth = image.attribute("width").as_int(265);
		/*SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string("tmw_desert_spacing.png"));
		set->texture = app->tex->Load(tmp.GetString());
		set->texWidth = tileset_node.attribute("texWidth").as_int();
		set->texHeight = tileset_node.attribute("texHeight").as_int();
		set->numTilesWidth = tileset_node.attribute("numTilesWidth").as_int();
		set->numTilesHeight = tileset_node.attribute("numTilesHeight").as_int();
		set->offsetX = tileset_node.attribute("offsetX").as_int();
		set->offsetY = tileset_node.attribute("offsetY").as_int();*/
	}

	return ret;
}

// L06: TODO 6: Load a group of properties from a node and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;

	//...
	return ret;
}
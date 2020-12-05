#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"
#include "Defs.h"
#include "Log.h"
#include"Player.h"
#include <math.h>

Map::Map(bool startEnabled) : Module(startEnabled), mapLoaded(false)
{
	name.Create("map");
}

// Destructor
Map::~Map() {}

// Ask for the value of a custom property
int Properties::GetProperty(const char* value, int defaultValue) const
{
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
	bool exit = false;

	// Prepare the loop to draw all tilesets + DrawTexture()
	TileSet* tileset;
	ListItem<MapLayer*>* layer = data.layers.start;

	// Make sure we draw all the layers and not just the first one
	while (layer != NULL)
	{
		for (int y = 0; y < data.height; ++y)
		{
			for (int x = 0; x < data.width; ++x)
			{
				int tileId = layer->data->Get(x, y);

				if (tileId > 0)
				{
					tileset = GetTilesetFromTileId(tileId);

					if (tileset->name == "colisiones")
					{

						ListItem<MapLayer*>* list1;
						list1 = data.layers.start;

						if (list1->data->properties.propety.propetyValue == 1)
						{
							exit = true;
							break;
						}
					}

					if (exit == false)
					{
						SDL_Rect rect = tileset->GetTileRect(tileId);
						iPoint point = MapToWorld(x, y);
						if (point.x + app->render->camera.x > -62 && point.x + app->render->camera.x < app->render->camera.w && point.y + app->render->camera.y >-62 && point.y + app->render->camera.y < app->render->camera.h)
						{
							app->render->DrawTexture(tileset->textureTile, point.x, point.y, &rect);
							if (tileset->name == "colisiones")
							{
								SDL_SetRenderDrawBlendMode(app->render->renderer, SDL_BLENDMODE_BLEND);
								SDL_SetRenderDrawColor(app->render->renderer, 0, 255, 255, 80);
								SDL_RenderFillRect(app->render->renderer, &app->player->playerDown->rect);

								SDL_SetRenderDrawColor(app->render->renderer, 0, 255, 255, 80);
								SDL_RenderFillRect(app->render->renderer, &app->player->playerRight->rect);

								SDL_SetRenderDrawColor(app->render->renderer, 0, 255, 255, 80);
								SDL_RenderFillRect(app->render->renderer, &app->player->playerLeft->rect);

							}
						}
					}
				}
			}
			if (exit == true)
			{
				exit = false;
				break;
			}
		}
		layer = layer->next;
	}
}

void Map::ChangeCollisionsDraw()
{
	ListItem<MapLayer*>* list1;
	list1 = data.layers.start;

	if (list1->data->properties.propety.propetyValue == 1)
	{
		list1->data->properties.propety.propetyValue = 0;
	}
	else
	{
		list1->data->properties.propety.propetyValue = 1;
	}
}

iPoint Map::MapToWorld(int x, int y) const
{
	iPoint ret(0, 0);

	// Add isometric map to world coordinates
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

int Map::numberToMap(int number) 
{
	return number / data.tileWidth;
}

// Add orthographic world to map coordinates
iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	// Add the case for isometric maps to WorldToMap
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

int Map::GetTileIdFromPosition(int x, int y,const char* layername) 
{
	ListItem<MapLayer*>* layer = data.layers.start;

	while (layer != nullptr) 
	{
		if (layer->data->name == layername) 
		{
			break;
		}
		layer=layer->next;
	}
	
	return layer->data->Get(x, y);
}

// Pick the right Tileset based on a tile id
TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* lista = data.tilesets.start;
	TileSet* set = lista->data;
	while (lista->data != nullptr) 
	{
		if (lista->next == nullptr) 
		{
			set = lista->data;
			break;
		}
		if ((lista->data->firstgid <= id) && (lista->next->data->firstgid > id)) 
		{
			set = lista->data;
			break;
		}
		lista = lista->next;
	}

	return set;
}

// Called before quitting
bool Map::CleanUp()
{
	ListItem<TileSet*>* item;
	item = data.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	data.tilesets.Clear();

	// Clean up the pugui tree
	ListItem<MapLayer*>* ite;
	ite = data.layers.start;
	while (ite != NULL)
	{
		RELEASE(ite->data);
		ite = ite->next;
	}
	data.layers.Clear();
	mapFile.reset();
	return true;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	// Get relative Tile rectangle
	// ORTHOGONAL
	rect.w = tileWidth;
	rect.h = tileHeight;
	int num = texWidth / tileWidth;
	int usa = id - firstgid + 1;
	int res = usa / num;
	int hond = usa % num;
	if (hond == 0) 
	{
		hond = num;
		res = res - 1;
	}
	hond = hond - 1;
	rect.x = hond * rect.w;
	rect.y = res * rect.h;

	//ISOMETRIC
	/*int res = id / 4;
	int hond = id % 4;
	if (hond == 0) {
		hond = 4;
		res = res - 1;
	}
	hond = hond - 1;
	rect.x = hond * rect.w;
	rect.y = res * rect.h;*/

	/*int relativeId = id - firstgid;
	rect.w = tileWidth;
	rect.h = tileHeight;
	rect.x = margin + ((rect.w + spacing) * (relativeId % 96));
	rect.y = margin + ((rect.h + spacing) * (relativeId / 96));*/

	return rect;
}

// Load new map
bool Map::Load(const char* filename)
{
	bool ret = true;
	SString tmp("%s%s", folder.GetString(), filename);

	pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
		ret = false;
	}

	// Load general info
	// Create and call a private function to load a tileset remember to support more any number of tilesets!
	pugi::xml_node tileset;
	for (tileset = mapFile.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if (ret == true) ret = LoadTilesetDetails(tileset, set);

		if (ret == true) ret = LoadTilesetImage(tileset, set);

		data.tilesets.Add(set);
	}

	if (ret == true)
	{
		// Create and call a private function to load and fill all your map data
		ret = LoadMap();
	}

	if (ret == true)
	{
		// LOG all the data loaded iterate all tilesets and LOG everything
		ListItem<TileSet*>* list1;
		list1 = data.tilesets.start;

		LOG("Succesfully parsed map XML file: snow_tileset.tmx", );
		LOG("width: %d tile_height: %d", data.width, data.height);
		LOG("tile_width: %d tile_heigh: %d", data.tileWidth, data.tileHeight);
	}

	pugi::xml_node layer;
	pugi::xml_node node2;
	ListItem<MapLayer*>* list2;

	for (layer = mapFile.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* lay = new MapLayer();

		ret = LoadLayer(layer, lay);

		if (ret == true)
			data.layers.Add(lay);

		node2 = layer.child("properties");
		list2 = data.layers.start;
		for (node2 = node2.child("property"); node2; node2 = node2.next_sibling("property"))
		{
			LoadProperties(node2, list2->data->properties);
		}
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
	int cant = layer->height * layer->width;
	layer->data = new uint[cant];
	memset(layer->data, 0, cant);
	pugi::xml_node node1 = node.child("data").child("tile");
	for (int i = 0; i < cant; i++) 
	{
		layer->data[i] = node1.attribute("gid").as_int();
		node1 = node1.next_sibling("tile");
	}

	return ret;
}

// Load map general properties
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
		// Load map general properties
		data.tileHeight = map.attribute("tileheight").as_int(32);
		data.tileWidth = map.attribute("tilewidth").as_int(32);
		node->data->numTilesHeight = map.attribute("height").as_int();
		node->data->numTilesWidth = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.width = map.attribute("width").as_int();
		SString tmp("%s", map.attribute("orientation").value());
		if (tmp == "orthogonal")
		{
			data.type = MapTypes::MAPTYPE_ORTHOGONAL;
		}
		else if (tmp == "isometric")
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

// Load Tileset attributes
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
		set->firstgid = tileset_node.attribute("firstgid").as_int();
		set->margin = tileset_node.attribute("margin").as_int();
		set->name = tileset_node.attribute("name").as_string();
		set->tile_width = tileset_node.attribute("tilewidth").as_int();
		set->tile_height = tileset_node.attribute("tileheight").as_int();
		set->tileHeight = tileset_node.attribute("tileheight").as_int();
		set->tileWidth = tileset_node.attribute("tilewidth").as_int();
		set->spacing = tileset_node.attribute("spacing").as_int();
	}

	return ret;
}

// Load Tileset image
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
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->textureTile = app->tex->Load(tmp.GetString());
		set->texHeight = image.attribute("height").as_int();
		set->texWidth = image.attribute("width").as_int();
		set->numTilesWidth = tileset_node.attribute("numTilesWidth").as_int();
		set->numTilesHeight = tileset_node.attribute("numTilesHeight").as_int();
		set->offsetX = tileset_node.attribute("offsetX").as_int();
		set->offsetY = tileset_node.attribute("offsetY").as_int();
	}

	return ret;
}

// Load a group of properties from a node and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = true;

	properties.propety.propetyName = node.attribute("name").as_string();
	properties.propety.propetyValue = node.attribute("value").as_int();

	return ret;

}
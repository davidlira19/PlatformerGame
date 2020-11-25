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
	ResetPath();
	app->map->goal.x = -1;
	app->map->goal.y = -1;
	return ret;
}
void Map::FindFinalPath() 
{
	bool pathFound = false;
	ListItem<iPoint>* selector1;
	ListItem<iPoint>* selector;
	ListItem<iPoint>* oldSelector = visited.end;
	while (pathFound == false)
	{
		finalPath.Add(oldSelector->data);
		if (oldSelector->data == visited.start->data)
		{
			pathFound = true;
			break;
		}
		selector = visited.start;
		selector1 = breadcrumps.start;
		while (selector != nullptr)
		{
			if (selector->data == oldSelector->data)
			{
				oldSelector->data = selector1->data;
				break;
			}
			else
			{
				selector = selector->next;
				selector1 = selector1->next;
			}
		}
	}
	/*List<iPoint> auxiliarList;
	ListItem<iPoint>*auxiliarListItem;
	auxiliarListItem= finalPath.end;
	for (int a = 0; a < finalPath.count() || auxiliarListItem!=nullptr; a++) {
		auxiliarList.Add(auxiliarListItem->data);
		auxiliarListItem=auxiliarListItem->prev;
	}
	finalPath.Clear();
	finalPath = auxiliarList;*/
}
void Map::PropagateAStar() 
{
	bool found = false;
	int counter = 0;
	iPoint start = { 16,4 };
	iPoint result;
	iPoint curr;
	iPoint neighbors[4];
	breadcrumps.Add(visited.start->data);
	curr = start;
	frontier.Clear();
	int h, g, minimum;
	ListItem<iPoint>* auxiliar = nullptr;
	ListItem<iPoint>* selected = nullptr;
	ListItem<iPoint>* secondAuxiliar = nullptr;

	//bucle
	for (int i = 0; i < app->map->data.tilesets.start->data->numTilesHeight * app->map->data.tilesets.start->data->numTilesWidth; i++)
	{
		neighbors[0].Create(curr.x, curr.y - 1);
		neighbors[1].Create(curr.x - 1, curr.y);
		neighbors[2].Create(curr.x, curr.y + 1);
		neighbors[3].Create(curr.x + 1, curr.y);

		for (int i = 0; i < 4; i++)
		{
			if (visited.Find(neighbors[i]) == -1 && IsWalkable(neighbors[i].x, neighbors[i].y) == true)
			{
				frontierr.Add(neighbors[i]);
				visited.Add(neighbors[i]);
				breadcrumps.Add(curr);

				h = neighbors[i].DistanceManhattan(goal);
				g = neighbors[i].DistanceManhattan(start);
				result.x = g;
				result.y = h;
				tileValue.Add(result);

			}
			if (neighbors[i] == goal)
			{
				found = true;
				counter = 0;
				break;
			}
		}
		if (found == true)
		{
			break;
		}


		minimum = tileValue.start->data.x + tileValue.start->data.y;
		secondAuxiliar = frontierr.start;
		selected = nullptr;
		auxiliar = tileValue.start;
		counter = 0;

		while (auxiliar != nullptr)
		{
			if ((auxiliar->data.x + auxiliar->data.y) <= minimum)
			{
				minimum = auxiliar->data.x + auxiliar->data.y;
				selected = auxiliar;
				counter++;

			}
			auxiliar = auxiliar->next;
		}

		if (counter - 1 > 1)
		{
			counter = 0;
			auxiliar = tileValue.start;
			while (auxiliar != nullptr)
			{
				if (auxiliar->data.y <= minimum)
				{
					minimum = auxiliar->data.y;
					selected = auxiliar;
					counter++;
				}
				auxiliar = auxiliar->next;
			}
		}

		auxiliar = tileValue.start;
		while (auxiliar != nullptr)
		{
			if (auxiliar == selected)
			{
				curr = secondAuxiliar->data;
				tileValue.Del(selected);
				frontierr.Del(secondAuxiliar);
				break;
			}
			else
			{
				auxiliar = auxiliar->next;
				secondAuxiliar = secondAuxiliar->next;
			}

		}

		counter = 0;





	}

	if (found == true)
	{

		FindFinalPath();
	}
}
void Map::PropagateBFS()
{
	bool found = false;
	
	// L10: TODO 1: If frontier queue contains elements
	// pop the last one and calculate its 4 neighbors
	iPoint curr;
	iPoint neighbors[4];
	breadcrumps.Add(visited.start->data);
	for (int i = 0; i < app->map->data.tilesets.start->data->numTilesHeight * app->map->data.tilesets.start->data->numTilesWidth; i++) {

		if (frontier.Pop(curr) == true)
		{
			neighbors[0].Create(curr.x, curr.y - 1);
			neighbors[1].Create(curr.x + 1, curr.y);
			neighbors[2].Create(curr.x, curr.y + 1);
			neighbors[3].Create(curr.x - 1, curr.y);

			for (int i = 0; i < 4; i++)
			{
				if (visited.Find(neighbors[i]) == -1 && IsWalkable(neighbors[i].x, neighbors[i].y) == true)
				{
					frontier.Push(neighbors[i]);
					visited.Add(neighbors[i]);
					breadcrumps.Add(curr);
				}
				if (neighbors[i] == goal)
				{
					found = true;
					break;
				}

			}
		}
		if (found == true) 
		{ 
			break; 
		}
	}

	if (found == true)
	{
		FindFinalPath();
	}
	// L10: TODO 2: For each neighbor, if not visited, add it
	// to the frontier queue and visited list
	
}
void Map::DrawPath()
{
	iPoint point;

	// Draw visited
	ListItem<iPoint>* item = visited.start;

	while (item)
	{
		point = item->data;
		TileSet* tileset = GetTilesetFromTileId(61);

		SDL_Rect rec = tileset->GetTileRect(61);
		iPoint pos = MapToWorld(point.x, point.y);

		app->render->DrawTexture(tileset->texture, pos.x, pos.y, &rec);

		item = item->next;
	}

	// Draw frontier
	for (uint i = 0; i < frontier.Count(); ++i)
	{
		point = *(frontier.Peek(i));
		TileSet* tileset = GetTilesetFromTileId(62);

		SDL_Rect rec = tileset->GetTileRect(62);
		iPoint pos = MapToWorld(point.x, point.y);

		app->render->DrawTexture(tileset->texture, pos.x, pos.y, &rec);
	}

	//draw final path
	ListItem<iPoint>* auxiliarItem = finalPath.start;

	while (auxiliarItem)
	{
		point = auxiliarItem->data;
		TileSet* tileset = GetTilesetFromTileId(25);

		SDL_Rect rec = tileset->GetTileRect(25);
		iPoint pos = MapToWorld(point.x, point.y);

		app->render->DrawTexture(tileset->texture, pos.x, pos.y, &rec);

		auxiliarItem = auxiliarItem->next;
	}

}
void Map::ResetPath()
{
	frontier.Clear();
	visited.Clear();
	breadcrumps.Clear();
	
	frontier.Push(iPoint(16,4));
	visited.Add(iPoint(16,4));
	/*finalPath.Clear();*/
}
bool Map::IsWalkable(int x, int y) const
{
	// L10: TODO 3: return true only if x and y are within map limits
	// and the tile is walkable (tile id 0 in the navigation layer)
	

	bool ret = false;

	if ((x < data.tilesets.start->data->numTilesWidth && x > 0) && (y < data.tilesets.start->data->numTilesHeight && y > 0) && (app->map->GetTileIdFromPosition(x, y, "colisions") != 61))
	{
		//&& data.tilesets.start->data->firstgid == 0
		ret = true;
	}
	
	
	return ret;
}
// Draw the map (all requried layers)
void Map::Draw()
{
	if (mapLoaded == false) return;
	bool exit = false;
	// L04: DONE 5: Prepare the loop to draw all tilesets + DrawTexture()
	TileSet* tileset;
	ListItem<MapLayer*>* layer = data.layers.start;
	// L06: TODO 4: Make sure we draw all the layers and not just the first one
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
						app->render->DrawTexture(tileset->texture, point.x, point.y, &rect);

					}
					

					// L04: DONE 9: Complete the draw function
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

int Map::GetTileIdFromPosition(int x, int y,const char* layername) {
	ListItem<MapLayer*>* layer = data.layers.start;
	while (layer != nullptr) {
		if (layer->data->name == layername) {
			break;
		}
		layer=layer->next;
	}
	
	return layer->data->Get(x, y);
}
// L06: TODO 3: Pick the right Tileset based on a tile id
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
	data.tilesets.Clear();

	// Clean up the pugui tree
	mapFile.reset();

	return true;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	// L04: DONE 7: Get relative Tile rectangle
	//ORTHOGONAL
	rect.w = tileWidth;
	rect.h = tileHeight;
	int num = texWidth / tileWidth;
	int usa=id-firstgid+1;
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


	// L03: DONE 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
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
		// L03: DONE 3: Create and call a private function to load and fill all your map data
		ret = LoadMap();
	}
	if (ret == true)
	{
		// L03: DONE 5: LOG all the data loaded iterate all tilesets and LOG everything
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
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->texture = app->tex->Load(tmp.GetString());
		set->texHeight = image.attribute("height").as_int();
		set->texWidth = image.attribute("width").as_int();
		set->numTilesWidth = tileset_node.attribute("numTilesWidth").as_int();
		set->numTilesHeight = tileset_node.attribute("numTilesHeight").as_int();
		set->offsetX = tileset_node.attribute("offsetX").as_int();
		set->offsetY = tileset_node.attribute("offsetY").as_int();
	}

	return ret;
}

// L06: TODO 6: Load a group of properties from a node and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = true;

	properties.propety.propetyName = node.attribute("name").as_string();
	properties.propety.propetyValue = node.attribute("value").as_int();


	return ret;
	//...
}
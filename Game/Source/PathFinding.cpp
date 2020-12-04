#include"PathFinding.h"
#include"App.h"
#include"Map.h"
#include"Render.h"
#include"Input.h"
PathFinding::PathFinding() 
{

}
PathFinding::~PathFinding()
{

}
bool PathFinding::PropagateAStar()
{
	bool found = false;
	int counter = 0;
	//iPoint start = { 16,4 };
	iPoint result;
	iPoint curr;
	iPoint neighbors[4];
	breadcrumps.Add(visited.start->data);
	curr = start;
	frontier.Clear();
	int h, g, minimum;
	semiFind = false;
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
				semiFind = true;
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
		if (semiFind == true) {
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
			semiFind = false;
		}
		else
		{
			break;
		}
	}

	if (found == true)
	{
		FindFinalPath();
		return true;
	}
	else {
		return false;
	}
}
bool PathFinding::ExistPath() 
{
	if (finalPath.start != nullptr) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}
bool PathFinding::IsWalkable(int x, int y) const
{
	// L10: TODO 3: return true only if x and y are within map limits
	// and the tile is walkable (tile id 0 in the navigation layer)


	bool ret = false;

	if ((x < app->map->data.tilesets.start->data->numTilesWidth && x > 0) && (y < app->map->data.tilesets.start->data->numTilesHeight && y > 0) && (app->map->GetTileIdFromPosition(x, y, "collisions") != 61) && (app->map->GetTileIdFromPosition(x, y, "collisions") != 62))
	{
		//&& data.tilesets.start->data->firstgid == 0
		ret = true;
	}


	return ret;
}
void PathFinding::DrawPath()
{
	//draw final path
	
		//Draw visited
		iPoint point;
		/*ListItem<iPoint>* item = visited.start;

		while (item)
		{
			point = item->data;
			TileSet* tileset = app->map->GetTilesetFromTileId(61);

			SDL_Rect rec = tileset->GetTileRect(61);
			iPoint pos = app->map->MapToWorld(point.x, point.y);
			tileset = app->map->data.tilesets.start->data;
			app->render->DrawTexture(tileset->textureTile, pos.x, pos.y, &rec);

			item = item->next;
		}

		for (uint i = 0; i < frontier.Count(); ++i)
		{
			point = *(frontier.Peek(i));
			TileSet* tileset = app->map->GetTilesetFromTileId(62);

			SDL_Rect rec = tileset->GetTileRect(62);
			iPoint pos = app->map->MapToWorld(point.x, point.y);

			app->render->DrawTexture(tileset->textureTile, pos.x, pos.y, &rec);
		}*/

		ListItem<iPoint>* auxiliarItem = finalPath.start;

		while (auxiliarItem)
		{
			point = auxiliarItem->data;
			TileSet* tileset = app->map->GetTilesetFromTileId(33);

			SDL_Rect rec = tileset->GetTileRect(33);
			iPoint pos = app->map->MapToWorld(point.x, point.y);

			app->render->DrawTexture(tileset->textureTile, pos.x, pos.y, &rec);

			auxiliarItem = auxiliarItem->next;
		}
	
}

	// Draw frontier

void PathFinding::ResetPath()
{
	frontier.Clear();
	visited.Clear();
	breadcrumps.Clear();
	////////////////////////////////
	///////////////////////////////////
	frontierr.Clear();
	//breadcrumps.Clear();
	tileValue.Clear();
	finalPath.Clear();
}
void PathFinding::FindFinalPath()
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
	int a;
	a = 0;
}
#ifndef _PATHFINDING_H_
#define _PATHFINDING_H_

#include"List.h"
#include"Queue.h"
#include"Point.h"

class PathFinding 
{

public:

	PathFinding();
	~PathFinding();
	bool PropagateAStar();
	void FindFinalPath();
	bool IsWalkable(int x, int y) const;
	void ResetPath();
	void DrawPath();
	bool ExistPath();
	iPoint goal;
	iPoint start;
	List<iPoint> visited;
	Queue<iPoint> frontier;
	List<iPoint> finalPath;
	bool semiFind;

private:

	List<iPoint> frontierr;
	List<iPoint> breadcrumps;
	List<iPoint> tileValue;
};

#endif
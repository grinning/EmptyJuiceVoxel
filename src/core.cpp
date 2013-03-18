/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#include <iostream>
#include <map>
#include <queue>

#include "../include/Loader.hpp"
#include "../include/Generator.hpp"
#include "../include/Rules.hpp"
#include "../include/UI.hpp"

/**
 * @file Core program that loads and runs modules
 *
 * Right now, it static links to exactly one of each type of module.
 *
 */

class Coord
{
	/**
	 * Temporary class for a coordinate
	 */
	int _x,_y,_z;
public:
	Coord(int x,int y,int z)
		:_x(x),_y(y),_z(z)
	{}
	bool operator <(const Coord& other) const
	{
		if(_x<other._x)
			return true;
		if(_x>other._x)
			return false;
		if(_y<other._y)
			return true;
		if(_y>other._y)
			return false;
		if(_z<other._z)
			return true;
		if(_z>other._z)
			return false;
		return false;
	}
};

struct ChunkWithCoord
{
	int x,y,z;
	EJV::Chunk *c;
};

std::map<Coord,EJV::Chunk *> cache; //Again temporary
std::queue<ChunkWithCoord> changedChunks;
std::queue<EJV::Action *> actions;

EJV::Chunk *getChunk(int x,int y,int z)
{
	EJV::Chunk *&req=cache[Coord(x,y,z)];

	if(req)
		return req;
	
	req=loadChunk(x,y,z);
	if(!req)
		req=generateChunk(x,y,z);

	return req;
}

void setChunk(int x,int y,int z,EJV::Chunk *c)
{
	cache[Coord(x,y,z)]=c;
	putChunk(x,y,z,c); //eventually, the cache will actually be used to prevent constantly writing changes

	ChunkWithCoord cwc={x,y,z,c};
	changedChunks.push(cwc);
}

//{get,set}Metadata() and displayMenu() will be linked together (for now).

void userAction(EJV::Action *act)
{
	actions.push(act);
}

int main(int argc,char *argv[])
{
	EJV::Action *nextAction;
	
	while(1)
	{
		if(actions.empty())
			nextAction=NULL;
		else
		{
			nextAction=actions.front();
			actions.pop();
		}
		
		tick(nextAction);

		for(;!changedChunks.empty();changedChunks.pop())
		{
			ChunkWithCoord cwc;
			cwc=changedChunks.front();
			
			updateChunk(cwc.x,cwc.y,cwc.z,cwc.c);
		}
	}
}

/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef LOADER_INCLUDED
#define LOADER_INCLUDED

#include <string>
#include <map>
#include <fstream>

#include "Loader.hpp"
#include "mNBT/RegionLoader.hpp"

/**
 * @file Loader module for the Anvil File Format.
 *
 */

/**
 * Map of chunk location to RegionLoader.
 */

struct RegionData {
	mNBT::RegionLoader* loader;
	short count; //Used to know when to empty a regionLoader.
};

std::map<std::pair<int,int>,RegionData*> loadMap;

extern "C"
{
	/**
	 * Run when the module is loaded.
	 * Does not load any chunks.
	 */
	void init() {}

	/**
	 * Run when the module is unloaded.
	 * Saves any files left.
	 */
	void destroy() {
		for (auto& it: loadMap) {
			it->second->loader->save();
			delete it->second->loader;
			delete it->second;
		}
		loadMap.clear();
		return;
	}

	/**
	 * Get a chunk from disc.
	 */
	EJV::Chunk *loadChunk(int x, int y, int z) {
		mNBT::Tag* chunk;
		std::pair <int,int> coords(x >> 5, z >> 5);
		if (loadMap.count(coords)) {
			chunk = loadMap[coords]->loader->getChunk(x % 32, z % 32);
		} else {
		mNBT::RegionLoader* newRegion = new mNBT::RegionLoader("world",x>>5,z>>5);
		RegionData* newLoader = new RegionData;
		newLoader->count = 1;
		newLoader->loader = newRegion;
		loadMap[coords] = newLoader;
		chunk = newRegion->getChunk(x,z);
		}
		if (chunk == NULL)
			return NULL;
		
	}

	/**
	 * Saves a chunk to the disc.
	 *
	 * @param x X chunk coord.
	 * @param y Y chunk coord.
	 * @param z Z chunk coord.
	 * @param c Chunk to save.B
	 */
	void putChunk(int x, int y, int z, EJV::Chunk *c);

	/**
	 * Releases a chunk.
	 *
	 * @param x X chunk coord.
	 * @param y Y chunk coord.
	 * @param z Z chunk coord.
	 * @param c Chunk to release.
	 */
	void releaseChunk(int x, int y, int z, EJV::Chunk *c);

	/**
	 * Get metadata about the world.
	 *
	 * @param which The name of the module.
	 * @return the metadata for that module.
	 */
	EJV::Metadata *getMetadata(const std::string& which);

	/**
	 * Sets the metadata for a sepecific module.
	 *
	 * @param which The name of the module.
	 * @param data The metadata to set.
	 */
	void setMetadata(const std::string& which, EJV::Metadata *data);
}

// EXTERNAL

/**
 * States that a chunk is no longer valid.
 * Used for networking and is external.
 *
 * @param x X chunk coord.
 * @param y Y chunk coord.
 * @param z Z chunk coord.
 */
void invalidateChunk(int x, int y, int z);

#endif //LOADER_INCLUDED

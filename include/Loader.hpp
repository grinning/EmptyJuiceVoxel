/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#ifndef LOADER_INCLUDED
#define LOADER_INCLUDED

#include <string>

#include "Chunk.hpp"
#include "Metadata.hpp"

/**
 * @file Interface for loader modules
 *
 */

namespace EJV {
	chunk *loadChunk(int x,int y,int z);
	void putChunk(int x,int y,int z,chunk *c);
	void releaseChunk(int x,int y,int z,chunk *c);
	void invalidateChunk(int x,int y,int z,chunk *c); //external

	metadata *getMetadata(std::string which);
	void setMetadata(std::string which,metadata *data);
}

#endif //LOADER_INCLUDED

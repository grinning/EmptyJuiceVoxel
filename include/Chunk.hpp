/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#ifndef CHUNK_INCLUDED
#define CHUNK_INCLUDED

#include <Metadata.hpp>

#include <map>

/**
 * @file Interface for chunks
 *
 */

#define CHUNK_WIDTH 32 //I just made these sizes up...
#define CHUNK_LENGTH 32
#define CHUNK_HEIGHT 32

namespace EJV {
	struct chunk {
		short[CHUNK_WIDTH][CHUNK_LENGTH][CHUNK_HEIGHT] blocks;

        std::map<int,std::map<std::string,metadata> data;
	};
}

#endif //CHUNK_INCLUDED

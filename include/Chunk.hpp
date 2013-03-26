/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef CHUNK_INCLUDED
#define CHUNK_INCLUDED

#include "Metadata.hpp"

#include <map>

#include <cstring>
#include <string>

/**
 * @file Interface for chunks
 *
 */

#define CHUNK_WIDTH  16
#define CHUNK_LENGTH 16
#define CHUNK_HEIGHT 16

namespace EJV
{
    struct Block : public Metadata
    {
        unsigned short ID;
    };

	struct Chunk
	{
		/**
		 * Short array indexed by [width][length][height] (xzy)
		 * representing blockdata.
		 */
        Block blocks[CHUNK_WIDTH][CHUNK_LENGTH][CHUNK_HEIGHT];
	};
}

#endif //CHUNK_INCLUDED

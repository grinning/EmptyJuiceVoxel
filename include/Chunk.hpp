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

	/**
	 * A chunk contains width * length * height blocks
	 * stored as shorts. It also contains a metadata map
	 * for various modules.
	 */
	struct Chunk
	{
		/**
		 * Map of (x + z * width + y * width * length) to a map of
		 * module name to metadata. -1 entry is chunk metadata.
		 */
		//typedef std::map<int, Metadata> MetadataMap;

		/**
		 * Short array indexed by [width][length][height] (xzy)
		 * representing blockdata.
		 */
        Block blocks[CHUNK_WIDTH][CHUNK_LENGTH][CHUNK_HEIGHT];

		//MetadataMap data;
	};
}

#endif //CHUNK_INCLUDED

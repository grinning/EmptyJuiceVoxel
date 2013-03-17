/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef GENERATOR_INCLUDED
#define GENERATOR_INCLUDED

#include "Chunk.hpp"

/**
 * @file Interface for generator modules
 *
 */
namespace EJV
{
    /**
     * Provides a chunk.
     *
     * @param x X chunk coord.
     * @param y Y chunk coord.
     * @param z Z chunk coord.
     * @return A generated chunk.
     */
	extern "C" Chunk *generateChunk(int x, int y, int z);
}

#endif //GENERATOR_INCLUDED

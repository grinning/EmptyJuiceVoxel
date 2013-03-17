/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef FLATLAND_INCLUDED
#define FLATLAND_INCLUDED

#include "Generator.hpp"

/**
 * @file Interface for generator modules
 *
 */

namespace EJV
{
    /**
     * Run when the module is loaded.
     * This allows for the module to
     * initialize based on configurations.
     */
    extern "C" void init();

    /**
     * Provides a flat chunk, 4 tall grass.
     *
     * @param x X chunk coord.
     * @param y Y chunk coord.
     * @param z Z chunk coord.
     * @return A generated chunk.
     */
	extern "C" Chunk *generateChunk(int x, int y, int z)
	{
        Chunk* toReturn = new Chunk;
        short* blocks = toReturn->blocks;
        short setBlock = 0; // air.
        if (!y) //If the bottom of the world
            setBlock = 1;//TODO: Change to proper number.
        for (unsigned int x = 0; x < 31; x++)
            for (unsigned int z = 0; z < 31; z++)
                for (unsigned int y = 0; y < 31; y++)
                    if (y < 4)
                        *blocks[x][z][y] = setBlock;
                    else
                        *blocks[x][z][y] = 0;
        return toReturn;
	}//So bad.
}

#endif //FLATLAND_INCLUDED

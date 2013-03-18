/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef PERLINGEN_INCLUDED
#define PERLINGEN_INCLUDED

#include "Generator.hpp"

/**
 * @file Perlin noise based terrain generator
 *
 */

namespace EJV
{
    extern "C"
    {
        /**
         * Run when the module is loaded.
         * This allows for the module to
         * initialize based on configurations.
         */
        extern "C" void init() {}

        /**
         * Run when the module is unloaded.
         * This allows modules to close files,
         * end connections, and clean up.
         */
        extern "C" void destroy() {}

        /**
         * Provides a chunk.
         *
         * @param x X chunk coord.
         * @param y Y chunk coord.
         * @param z Z chunk coord.
         * @return A generated chunk.
         */
        extern "C" Chunk *generateChunk(int x, int y, int z)
        {
            Chunk* newChunk = new Chunk;

            return newChunk;
        }
    }
}

#endif //PERLINGEN_INCLUDED

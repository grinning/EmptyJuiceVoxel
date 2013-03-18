/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef FLATLAND_INCLUDED
#define FLATLAND_INCLUDED

#include "Generator.hpp"

/**
 * @file Flatworld generator module interface.
 *
 */

namespace EJV
{
    extern "C"
    {
        static unsigned int   HEIGHT;
        static unsigned short BLOCK_TYPE;

        /**
         * Run when the module is loaded.
         * This allows for the module to
         * initialize based on configurations.
         */
        void init()
        {
            // Defaults
            HEIGHT = 4;
            BLOCK_TYPE = 1;
        }

        /**
         * Run when the module is unloaded.
         * This allows modules to close files,
         * end connections, and clean up.
         */
        void destroy() {}

        /**
         * Provides a flat chunk, 4 tall grass.
         *
         * @param x X chunk coord.
         * @param y Y chunk coord.
         * @param z Z chunk coord.
         * @return A generated chunk.
         */
        Chunk *generateChunk(int chunkX, int chunkY, int chunkZ)
        {
            Chunk* newChunk = new Chunk;

            unsigned short newBlock = chunkY ? BLOCK_TYPE : 0;

            for (unsigned short x = 0; x < CHUNK_WIDTH; ++x)
                for (unsigned short z = 0; z < CHUNK_HEIGHT; ++z)
                    for (unsigned short y = 0; y < CHUNK_LENGTH; ++y)
                        if (y < 4)
                            newChunk->blocks[x][z][y] = newBlock;
                        else
                            newChunk->blocks[x][z][y] = 0;

            return newChunk;
        }
    }
}

#endif //FLATLAND_INCLUDED

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

extern "C"
{
    /**
     * Run when the module is loaded.
     * This allows for the module to
     * initialize based on configurations.
     */
    void init();

    /**
     * Run when the module is unloaded.
     * This allows modules to close files,
     * end connections, and clean up.
     */
    void destroy();

    /**
     * Provides a chunk.
     *
     * @param x X chunk coord.
     * @param y Y chunk coord.
     * @param z Z chunk coord.
     * @return A generated chunk.
     */
    EJV::Chunk *generateChunk(int x, int y, int z);
}

#endif //GENERATOR_INCLUDED

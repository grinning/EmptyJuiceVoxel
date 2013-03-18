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
     * Get a chunk from disc.
     *
     * @param x X chunk coord.
     * @param y Y chunk coord.
     * @param z Z chunk coord.
     * @return Pointer to a chunk if sucess, NULL otherwise.
     */
    EJV::Chunk *loadChunk(int x, int y, int z);

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

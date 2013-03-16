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
namespace EJV
{
    /**
     * Get a chunk from disc.
     *
     * @param x X chunk coord.
     * @param y Y chunk coord.
     * @param z Z chunk coord.
     * @return Pointer to a chunk if sucess, NULL otherwise.
     */
	Chunk *loadChunk(int x, int y, int z);

	/**
	 * Saves a chunk to the disc.
	 *
     * @param x X chunk coord.
     * @param y Y chunk coord.
     * @param z Z chunk coord.
     * @param c Chunk to save.B
     */
	void putChunk(int x, int y, int z, Chunk *c);

	/**
     * Releases a chunk.
     *
     * @param x X chunk coord.
     * @param y Y chunk coord.
     * @param z Z chunk coord.
     * @param c Chunk to release.
     */
	void releaseChunk(int x, int y, int z, Chunk *c);

	/**
	 * States that a chunk is no longer valid.
	 * Used for networking and is external.
	 *
     * @param x X chunk coord.
     * @param y Y chunk coord.
     * @param z Z chunk coord.
	 */
	void invalidateChunk(int x, int y, int z); //external

    /**
     * Get metadata about the world.
     *
     * @param which The name of the module.
     * @return the metadata for that module.
     */
	Metadata *getMetadata(const std::string& which);

	/**
	 * Sets the metadata for a sepecific module.
	 *
	 * @param which The name of the module.
	 * @param data The metadata to set.
	 */
	void setMetadata(const std::string& which, Metadata *data);
}

#endif //LOADER_INCLUDED

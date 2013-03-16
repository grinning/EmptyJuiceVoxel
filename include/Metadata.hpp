/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#ifndef METADATA_INCLUDED
#define METADATA_INCLUDED

/**
 * @file Interface for metadata
 *
 */

namespace EJV {
    /**
     * Structure for module specific metadata
     * about blocks, chunks, or worlds.
     * Hold a basic void* pointer and a size.
     */
	struct metadata {
		int size;
		void *data;
	}
}

#endif //METADATA_INCLUDED

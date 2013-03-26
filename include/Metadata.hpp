/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef METADATA_INCLUDED
#define METADATA_INCLUDED

#include <stdexcept>
#include <map>

/**
 * @file Interface for metadata
 *
 */

namespace EJV
{
	/**
	 * Structure for module specific metadata
	 * about blocks, chunks, or worlds.
	 * Hold a basic void* pointer and a size.
	 */
	/*struct Metadata
	{
		int size;

		void *data;
	};*/

	// My proposal -Andrew
	struct Metadata
	{
	    typedef std::map<const std::string, void*> MetadataMap;

	    MetadataMap data;

	    template <typename T>
	    inline T& getMetadata(const std::string& name)
	    {
	        T* ptr = (T*) data[name];

	        // Temporary
	        if (!ptr) throw std::runtime_error("Invalid metadata");

	        return *ptr;
	    }
	};
}

#endif //METADATA_INCLUDED

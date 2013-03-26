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

	// My proposal -Andrew + Invalid
	struct Metadata
	{
	    typedef std::map<const unsigned int, void*> MetadataMap;

	    MetadataMap data;

	    template <typename T>
	    inline T& getMetadata(unsigned int id)
	    {
            MetadataMap::iterator it = data.find(id);

            // Lol out of range
            if(it == data.end()) throw std::runtime_error("Invalid metadata ID");

            return *((T*)it->second);
	    }
	};
}

#endif //METADATA_INCLUDED

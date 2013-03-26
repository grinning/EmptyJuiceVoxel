/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/

#ifndef METADATA_INCLUDED
#define METADATA_INCLUDED

#include <stdexcept>
#include <vector>

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
	    typedef std::vector<void*> MetadataList;

	    MetadataList data;

	    template <typename T>
	    inline T& getMetadata(unsigned int id)
	    {
            if (id > data.size()) throw std::runtime_error("Out of range");

            T* ptr = (T*) data[id];

            if (!ptr) throw std::runtime_error("Invalid metadata");

            return *ptr;
	    }

        unsigned int registerData(void* metadata)
        {
            if (!metadata) return 0;

            data.push_back(metadata);

            return data.size() - 1;
        }

        unsigned int getNumMetadata() const { return data.size(); }

        bool isRegistered(const unsigned int& id) const { return id < data.size(); }
	};
}

#endif //METADATA_INCLUDED

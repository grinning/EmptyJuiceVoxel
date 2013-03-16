/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#ifndef BLOCK_INCLUDED
#define BLOCK_INCLUDED

#include <map>
#include <string>

#include "metadata.hpp"

/**
 * @file Interface for blocks
 *
 */

namespace EJV {
	struct block {
		int id;
		std::map(std::string,metadata) data;
	};
}

#endif //BLOCK_INCLUDED

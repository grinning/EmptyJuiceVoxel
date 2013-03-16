/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#ifndef GENERATOR_INCLUDED
#define GENERATOR_INCLUDED

#include "chunk.hpp"

/**
 * @file Interface for generator modules
 *
 */

namespace EJV {
	chunk *genChunk(int x,int y,int z);
}

#endif //GENERATOR_INCLUDED

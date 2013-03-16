/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#ifndef RULES_INCLUDED
#define RULES_INCLUDED

#include <string>

#include "action.hpp"
#include "chunk.hpp"
#include "metadata.hpp"
#include "menu.hpp"

/**
 * @file Interface for rules modules
 *
 */

namespace EJV {
	void tick(action *act);

	chunk *getChunk(int x,int y,int z); //external
	void setChunk(int x,int y,int z,chunk *c); //external

	metadata *getMetadata(std::string which); //external
	void setMetadata(std::string which,metadata* data); //external

	void selectMenu(menu *m); //external
}

#endif //RULES_INCLUDED

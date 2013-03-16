/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#ifndef UI_INCLUDED
#define UI_INCLUDED

#include "Chunk.hpp"
#include "Action.hpp"
#include "Menu.hpp"

/**
 * @file Interface for UI modules
 *
 */

namespace EJV {
	void updateChunk(int x,int y,int z,chunk *c);

	chunk *getChunk(int x,int y,int z); //external

	void userAction(action* act); //external

	void displayMenu(menu *m);
}

#endif //UI_INCLUDED

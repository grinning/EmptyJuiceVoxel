/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#ifndef MENU_INCLUDED
#define MENU_INCLUDED

#include "chunk.hpp"

/**
 * @file Interface for menus
 *
 */

namespace EJV {
	enum menuType {
		//fill this in...
	};
	
	struct menu {
		menuType type;
		union data {
			//this too...
		}	
	}
}

#endif //MENU_INCLUDED

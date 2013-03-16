/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#ifndef MENU_INCLUDED
#define MENU_INCLUDED

#include "Chunk.hpp"

/**
 * @file Interface for menus
 *
 */

namespace EJV
{
	enum MenuType
	{
		//fill this in...
	};

    // Once again I recommend we use inheritance instead of unions -Dot
	struct Menu
	{
		MenuType type;

		union Data
		{
			//this too...
		}
	}
}

#endif //MENU_INCLUDED

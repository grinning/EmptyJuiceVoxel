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
		MENU_UNKNOWN,

		MENU_MAIN,

		MENU_SINGLEPLAYER,
		MENU_MULTIPLAYER,
		MENU_OPTIONS,

		// In-game ?
		MENU_BLOCK,

		MENU_COUNT
	};

	struct Menu
	{
		MenuType type;
		void *data;
	};
}

#endif //MENU_INCLUDED

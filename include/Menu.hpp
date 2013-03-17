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

    // Once again I recommend we use inheritance instead of unions -Andrew
	/*struct Menu
	{
		MenuType type;

		union Data
		{
			//this too...
		}
	}*/

	// My proposal -Andrew + Invalid
	namespace Menu
	{
	    struct Base
	    {
	        const MenuType type;

	        inline Base(MenuType t) : type(t >= MENU_COUNT ? MENU_UNKNOWN : t) {}
	    };

	    struct Main : public Base
	    {
	        inline Main() : Base(MENU_MAIN) {}
	    };

	    struct Singleplayer : public Base
	    {
	        inline Singleplayer() : Base(MENU_SINGLEPLAYER) {}
	    };

	    struct Multiplayer : public Base
	    {
	        inline Multiplayer() : Base(MENU_MULTIPLAYER) {}
	    };

	    struct Block : public Base
	    {
	        inline Block() : Base(MENU_BLOCK) {}
	    };
	}
}

#endif //MENU_INCLUDED

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
		MENU_MAIN,

		MENU_SINGLEPLAYER,
		MENU_MULTIPLAYER,
		MENU_OPTIONS,

		// In-game ?
		MENU_BLOCK
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

	// My proposal -Andrew
	namespace Menu
	{
	    struct Base
	    {
	        virtual MenuType getType() const = 0;

	        // TODO: Add more info (position, state e.t.c.)
	    };

	    struct Main : public Base
	    {
	        virtual MenuType getType() const { return MENU_MAIN; }
	    };

	    struct Singleplayer : public Base
	    {
	        virtual MenuType getType() const { return MENU_SINGLEPLAYER; }
	    };

	    struct Multiplayer : public Base
	    {
	        virtual MenuType getType() const { return MENU_MULTIPLAYER; }
	    };

	    struct Block : public Base
	    {
	        virtual MenuType getType() const { return MENU_BLOCK; }
	    };
	}
}

#endif //MENU_INCLUDED

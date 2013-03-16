/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#ifndef ACTION_INCLUDED
#define ACTION_INCLUDED

#include "Chunk.hpp"

/**
 * @file Interface for actions
 *
 */

namespace EJV {
	enum actionType {
		ITEMUSE,
		ITEMCHANGE,
		KEYPRESS,
		MENUSELECT
		//what else am I missing?
	};

	enum itemUseType {
		PRIMARY, //left click
		SENCONDARY, //right click
		CANCEL //ESC
	};

	enum keyboardKey {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		JUMP,
		SNEAK,
		INVENTORY,
		DROP
		//is this everything?
	}

	struct menu {
		actionType type;
		union data {
			itemUseType itemUsed;
			int changedTo;
			keyboardKey key;
			struct {
				//however you want to do menus...
			}
		}
	}
}

#endif //ACTION_INCLUDED

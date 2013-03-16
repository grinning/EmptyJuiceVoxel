/*#****************************************************************#*
 * Empty Juice Voxel: Minecraft clone by the Empty Juice Box Group  *
 * www              : http://www.juicebox.ckef-worx.com             *
 * Copyright (c) Empty Juice Box Group :: All Rights Reserved       *
 *#****************************************************************#*/
#ifndef ACTION_INCLUDED
#define ACTION_INCLUDED

#include "chunk.hpp"

/**
 * @file Interface for actions
 *
 */

namespace EJV {
	enum actionType {
		itemUse,
		itemChange,
		keypress,
		menuSelect
		//what else am I missing?
	};

	enum itemUseType {
		primary, //left click
		secondary, //right click
		cancel
	};

	enum keyboardKey {
		forward,
		backward,
		left,
		right,
		jump,
		sneak,
		inventory,
		drop
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

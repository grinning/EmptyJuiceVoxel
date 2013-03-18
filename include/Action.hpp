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

namespace EJV
{
	enum ActionType
	{
		ACTION_UNKNOWN,

		ACTION_ITEM_USE,
		ACTION_ITEM_CHANGE,

		ACTION_KEY_PRESS,

		ACTION_MENU_SELECT,

		ACTION_CHAT,

		ACTION_COUNT
	};

	enum ItemUseType
	{
		ITEM_USE_PRIMARY,
		ITEM_USE_SENCONDARY,
		ITEM_USE_CANCEL
	};

	enum KeyboardKey
	{
		// Movement
		KEY_FORWARD,
		KEY_BACKWARD,
		KEY_LEFT,
		KEY_RIGHT,

		// Stance
		KEY_JUMP,
		KEY_SNEAK,

		// Items
		KEY_INVENTORY,
		KEY_DROP
	};

	struct Action
	{
		ActionType type;
		void *data;
	};
}

#endif //ACTION_INCLUDED
